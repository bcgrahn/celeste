#include "Player.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Scale.h"
#include "iostream"
#include "Animation.h"

using namespace std;

Player::Player(string playerID, sf::RenderWindow* window)
{
    window_ptr = window;
    scorePts = 0;
    score.setString(to_string(scorePts));
    Scale scale;
    name type;
    rowsJumpedOn.push_back(false);
    rowsJumpedOn.push_back(false);
    rowsJumpedOn.push_back(false);
    rowsJumpedOn.push_back(false);

    font.loadFromFile("resources/AtariFont.ttf");
    score.setFont(font);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::White);

    if(playerID == "Player 1")
    {
        playerIdentity = 1;
        type = P1;
        //baileyTexture.loadFromFile("resources/madeline.png");
        baileyTexture.loadFromFile("resources/spritesheettest2.png");
        rectSourceSprite = sf::IntRect(0, 0, 400, 599.5);
        player.setTexture(baileyTexture);
        player.setTextureRect(rectSourceSprite);
        player.setPosition(sf::Vector2f(650.f, 199.f));
        //player.scale(sf::Vector2f(get<0>(scale.getScale(type)), get<1>(scale.getScale(type))));
        player.scale(sf::Vector2f(0.55,0.55));
        xScore = 1000.f;
        sf::Vector2u imageCount(4,4);
        float switchTime = 0.5f;
        play1Animation = new Animation(&baileyTexture, imageCount, switchTime, &rectSourceSprite);
    }
    else
    {
        playerIdentity = 2;
        type = P2;
        //baileyTexture.loadFromFile("resources/madeline2.png");
        baileyTexture.loadFromFile("resources/spritesheettest2.png");
        rectSourceSprite = sf::IntRect(0, 0, 400, 599.5);
        player.setTextureRect(rectSourceSprite);
        player.setTexture(baileyTexture);
        player.setPosition(sf::Vector2f(550.f, 199.f));
        //player.scale(sf::Vector2f(get<0>(scale.getScale(type)), get<1>(scale.getScale(type))));
        player.scale(sf::Vector2f(0.55,0.55));
        xScore = 20.f;
        sf::Vector2u imageCount(4,4);
        float switchTime = 0.5f;
        play1Animation = new Animation(&baileyTexture, imageCount, switchTime, &rectSourceSprite);

    }
    status = 'S';
    score.setPosition(xScore, 10.f);
    clockTime.restart();
}

void Player::jumpedOnRow(int rowNumber)
{
    bool condition = false;
    if((onCurrentRow != rowNumber) && (rowNumber !=-1))
    {
        onCurrentRow = rowNumber;

        if(rowsJumpedOn[onCurrentRow - 1] == false)
        {
            rowsJumpedOn[onCurrentRow - 1] = true;
            numFloesJumpedOn++;
            addPoints();
        }
    }
    else
    {
        condition = landedOnAllRows();
    }

    onCurrentRow = rowNumber;
}

bool Player::isAlive()
{
    return isAliveState;
}
int Player::onWhatRow()
{
    return onCurrentRow;
}
void Player::addPoints()
{
    scorePts = scorePts + 100;
    score.setString(to_string(scorePts)+" pts");
}
bool Player::landedOnAllRows()
{
    for(auto element: rowsJumpedOn)
    {
        if(!element)
        {
            return false;
        }
    }

    //reset jumped on
    for(int i = 0; i < rowsJumpedOn.size(); i++)
    {
        rowsJumpedOn[i] = false;
    }

    scorePts = scorePts - 100;
    return true;

}
bool Player::inSafeZone()
{
    return (player.getPosition().y <= 300.f);
}
bool Player::onIceFloe(bool status)
{
    onCloud = status;
}
void Player::resetNumFloesJumped()
{
    numFloesJumpedOn = 0;
}
void Player::decreaseNumFloesJumped()
{
    if(numFloesJumpedOn > 0)
    {
        numFloesJumpedOn--;
    }
}
void Player::jump()
{
    status = 'U';
    if(player.getPosition().y>(119+22) && !isFallingBool)
    {
        if(jumpDownFinished)
        {
            jumpUpFinished = false;
            if(count < 10)
            {
                player.move(0.f,-13.f);
                count++;
            }
            else
            {
                if(count < 13)
                {
                    player.move(0.f, 7.3333333333333f);
                    count++;
                }
                else
                {
                    count = 0;
                    jumpUpFinished = true;
                }
            }
        }
    }
}

void Player::jumpDown()
{
    status = 'J';
    if((player.getPosition().y<(119 + 5*108))&& !isFallingBool)
    {
        if(jumpUpFinished)
        {
            jumpDownFinished = false;
            if(count < 3)
            {
                player.move(0.f, -7.3333333333333f);
                count++;
            }
            else
            {
                if(count < 13)
                {
                    player.move(0.f,13.f);
                    count++;
                }
                else
                {
                    count = 0;
                    jumpDownFinished = true;
                }
            }
        }
    }
}

float Player::getY()
{
    return player.getPosition().y;
}

float Player::getX()
{
    return (player.getPosition().x);
}

void Player::update()
{
    isFallingBool = false;
    deltaTime = clockTime.getElapsedTime().asSeconds()*3.f;

    if(!jumpUpFinished)
    {
        jump();
    }
    else if(!jumpDownFinished)
    {
        jumpDown();
    }
    else if((!onCloud) && !inSafeZone())
    {
        move(0.f, 9.f);
        isFallingBool = true;
    }

    int row = 0;

    switch (status){
        case 'S':
            row = 0;
            deltaTime = 0;
            break;
        case 'J':
            row = 0;
            deltaTime = 0;
            break;
        case 'L':
            row = 2;
            break;
        case 'R':
            row = 3;
            break;
         case 'U':
            row = 1;
            break;
        default:
            row = 0;
            break;
    }

    play1Animation->update(row,deltaTime);
    player.setTextureRect(rectSourceSprite);
    window_ptr->draw(score);
    window_ptr->draw(player);
    clockTime.restart();
}

void Player::move(float x, float y)
{
    if(x>0)
    {
        status = 'R';
        if(player.getPosition().x<=(window_ptr->getSize().x-45))
        {
            if(jumpUpFinished && jumpDownFinished)
            {
                player.move(x,0.f);
            }
        }
    }
    else if(x<0)
    {
        status = 'L';
        if(player.getPosition().x>=0)
        {
            if(jumpUpFinished && jumpDownFinished)
            {
                player.move(x,0.f);
            }
        }
    }
    else{
        status = 'S';
    }

    if(y>0)
    {
        if(player.getPosition().y<=(window_ptr->getSize().y-10))
        {
            if(jumpUpFinished && jumpDownFinished)
            {
                player.move(0.f,y);
            }
        }
        else{
            isAliveState = false;
        }
    }
    else
    {
        if(player.getPosition().y>=0)
        {
            if(jumpUpFinished && jumpDownFinished)
            {
                player.move(0.f,y);
            }
        }
    }

}

bool Player::isFalling()
{
    return isFallingBool;
}

int Player::getTotalCloudsJumped()
{
    return numFloesJumpedOn;
}

vector<bool> Player::getRowsJumpedOn()
{
    return rowsJumpedOn;
}

int Player::getPlayerID()
{
    return playerIdentity;
}

bool Player::playerAtCastleEntrance(int cX, int cY)
{
    int x = player.getPosition().x;
    int y = player.getPosition().y;
    if(abs(y - 199) <= 2)
    {
            if(((cX - x) < 20)&&(x < (cX + 30))){
                return true;
            }
    }
    return false;
}
sf::Sprite Player::getPlayerSprite(){
    return player;
}

void Player::setAliveStatus(bool stat){
    isAliveState = stat;
}

