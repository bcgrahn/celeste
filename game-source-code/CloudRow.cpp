#include "CloudRow.h"
#include <vector>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

CloudRow::CloudRow(int rowN, vector<Player*>& players, sf::RenderWindow* window)
{
    speed = 2.f;
    rowNum = rowN;
    window_ptr = window;
    playerVec = &players;

    switch (rowNum)
    {
    case 1:
        yPos = 354.f;
        firstXPos = -120.f;
        orientation = "R";
        break;
    case 2:
        yPos = 462.f;
        firstXPos = 1300.f;
        orientation = "L";
        break;

    case 3:
        yPos = 570.f;
        firstXPos = -120.f;
        orientation = "R";
        break;
    case 4:
        yPos = 678.f;
        firstXPos = 1300.f;
        orientation = "L";
        break;
    default:
        yPos = 354.f;
        firstXPos = -120.f;
        orientation = "R";
        break;
    }

    auto xDif = 160.f;

    if (orientation == "R")
    {
        xDif =  xDif;
    }
    else
    {
        xDif = -xDif;
    }

    //Texture
    cloudU.loadFromFile("resources/CloudUpper.png");
    sf::Sprite platCloudU1;
    platCloudU1.setTexture(cloudU);
    platCloudU1.setPosition(sf::Vector2f(firstXPos, yPos));
    platCloudU1.scale(sf::Vector2f(3.5f, 3.5f));

    //Upper cloud
    sf::Sprite platCloudU2;
    platCloudU2.setTexture(cloudU);
    platCloudU2.setPosition(sf::Vector2f(firstXPos + 1*xDif, yPos));
    platCloudU2.scale(sf::Vector2f(3.5f, 3.5f));

    sf::Sprite platCloudU3;
    platCloudU3.setTexture(cloudU);
    platCloudU3.setPosition(sf::Vector2f(firstXPos + 2*xDif, yPos));
    platCloudU3.scale(sf::Vector2f(3.5f, 3.5f));

    sf::Sprite platCloudU4;
    platCloudU4.setTexture(cloudU);
    platCloudU4.setPosition(sf::Vector2f(firstXPos + 3*xDif, yPos));
    platCloudU4.scale(sf::Vector2f(3.5f, 3.5f));

    platCloudUpperVec.push_back(platCloudU1);                                  //Change cloudvec to a vector of pointer sprites and not sprite objects
    platCloudUpperVec.push_back(platCloudU2);
    platCloudUpperVec.push_back(platCloudU3);
    platCloudUpperVec.push_back(platCloudU4);

    cloudL.loadFromFile("resources/CloudLower.png");
    sf::Sprite platCloudL1;
    platCloudL1.setTexture(cloudL);
    platCloudL1.setPosition(sf::Vector2f(firstXPos, yPos));
    platCloudL1.scale(sf::Vector2f(3.5f, 3.5f));

    //LOwer cloud
    sf::Sprite platCloudL2;
    platCloudL2.setTexture(cloudL);
    platCloudL2.setPosition(sf::Vector2f(firstXPos + 1*xDif, yPos));
    platCloudL2.scale(sf::Vector2f(3.5f, 3.5f));

    sf::Sprite platCloudL3;
    platCloudL3.setTexture(cloudL);
    platCloudL3.setPosition(sf::Vector2f(firstXPos + 2*xDif, yPos));
    platCloudL3.scale(sf::Vector2f(3.5f, 3.5f));

    sf::Sprite platCloudL4;
    platCloudL4.setTexture(cloudL);
    platCloudL4.setPosition(sf::Vector2f(firstXPos + 3*xDif, yPos));
    platCloudL4.scale(sf::Vector2f(3.5f, 3.5f));

    platCloudLowerVec.push_back(platCloudL1);                                  //Change cloudvec to a vector of pointer sprites and not sprite objects
    platCloudLowerVec.push_back(platCloudL2);
    platCloudLowerVec.push_back(platCloudL3);
    platCloudLowerVec.push_back(platCloudL4);

    cloudP1.loadFromFile("resources/P1Cloud.png");
    cloudP2.loadFromFile("resources/P2Cloud.png");
    cloudP1Lower.loadFromFile("resources/P1CloudLower.png");
}


void CloudRow::update()
{
    auto player_ptr = (*playerVec)[0];
    vector<bool>rowsJumpedOn = player_ptr->getRowsJumpedOn();
    for(auto& element : platCloudUpperVec)
    {
        if(orientation == "R")
        {
            element.move(speed, 0.f);
            if(element.getPosition().x > 1290)
            {
                element.setPosition(firstXPos, yPos);
            }
        }
        else
        {
            element.move(-speed, 0.f);
            if(element.getPosition().x <-110)
            {
                element.setPosition(firstXPos, yPos);
            }
        }

        if(rowsJumpedOn[rowNum -1])
        {
            element.setTexture(cloudP1);
        }
        else
        {
            element.setTexture(cloudU);
        }


        window_ptr->draw(element);
    }

    for(auto& element : platCloudLowerVec)
    {
        if(orientation == "R")
        {
            element.move(speed, 0.f);
            if(element.getPosition().x > 1290)
            {
                element.setPosition(firstXPos, yPos);
            }
        }
        else
        {
            element.move(-speed, 0.f);
            if(element.getPosition().x <-110)
            {
                element.setPosition(firstXPos, yPos);
            }
        }

        if((*playerVec).size()>1)
        {

            auto player_ptr = (*playerVec)[1];
            vector<bool>rowsJumpedOn = player_ptr->getRowsJumpedOn();

            if(rowsJumpedOn[rowNum -1])
            {
                element.setTexture(cloudP2);
            }
            else
            {
                element.setTexture(cloudL);
            }

        }
        else{
            if(rowsJumpedOn[rowNum -1])
            {
                element.setTexture(cloudP1Lower);
            }
            else
            {
                element.setTexture(cloudL);
            }
        }

        window_ptr->draw(element);
    }

}

void CloudRow::collision()
{
    float cloudWidth = 75;
    float playerWidth = 35;
    float playerHeight = 103;
    float yCloudPos = 0.f;
    float xCloudPos = 0.f;

    for(auto* player_ptr : (*playerVec))
    {
        int onRow = false;
        for(auto& element : platCloudUpperVec)
        {

            yCloudPos = element.getPosition().y;
            xCloudPos = element.getPosition().x;

            if(((-player_ptr->getY() + yCloudPos - 47.f) <= 0.1f) && ((-player_ptr->getY() + yCloudPos - 47.f) >= -0.1))
            {

                if((xCloudPos + cloudWidth >= player_ptr->getX()) && (player_ptr->getX() >= xCloudPos - playerWidth))
                {
                    player_ptr->onIceFloe(true);
                    player_ptr->jumpedOnRow(rowNum);
                    onRow = true;
                    //cout << "landed on row " << rowNum << endl;

                    if(orientation == "R")
                    {
                        player_ptr->move(speed, 0.f);

                    }
                    else
                    {
                        player_ptr->move(-speed, 0.f);
                    }
                    break;
                }
                else
                {
                }
            }
            else
            {
            }

        }
    }
}

void CloudRow::changeDirection()
{
    if(orientation == "R")
    {
        orientation = "L";
        firstXPos = 1300.f;
        //cout << "change" << endl;
    }
    else
    {
        orientation = "R";
        firstXPos = -120.f;
        //cout << "change" << endl;
    }
}

void CloudRow::cloudsJumpedOn()
{
    for(auto* player_ptr : (*playerVec))
    {
        int playerID = player_ptr->getPlayerID();
        int count = 0;
        vector<bool>rowsJumpedOn = player_ptr->getRowsJumpedOn();
        if(rowsJumpedOn[rowNum - 1])
        {
            if(playerID == 1)
            {
                for(auto& element : platCloudUpperVec)
                {
                    element.setTexture(cloudP1);
                }
            }
            else
            {
                for(auto& element : platCloudLowerVec)
                {
                    element.setTexture(cloudP2);
                }
            }
        }
        else
        {
            if(playerID == 1)
            {
                for(auto& element : platCloudUpperVec)
                {
                    element.setTexture(cloudU);
                }
            }
            else
            {
                for(auto& element : platCloudLowerVec)
                {
                    element.setTexture(cloudL);
                }
            }
        }

    }
}

