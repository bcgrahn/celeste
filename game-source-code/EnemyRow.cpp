#include "EnemyRow.h"
#include <vector>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

EnemyRow::EnemyRow(int rowE, vector<Player *> &players, sf::RenderWindow *window, int enemyId)
{

    rowNum = rowE;
    window_ptr = window;
    playerVec = &players;
    sf::FloatRect getGlobalBounds;

    switch (rowNum)
    {
    case 1:
        yPos = 310.f;
        firstXPos = 1900.f;
        orientation = "L";
        break;
    case 2:
        yPos = 420.f;
        firstXPos = -1800.f;
        orientation = "R";
        break;
    case 3:
        yPos = 530.f;
        firstXPos = 1500.f;
        orientation = "L";
        break;
    case 4:
        yPos = 638.f;
        firstXPos = -2322.f;
        orientation = "R";
        break;
    default:
        yPos = 354.f;
        firstXPos = 1300.f;
        orientation = "L";
        break;
    }

    switch (enemyId)
    {
    case 1:
        enemy1.loadFromFile("resources/enemy1.png");
        break;
    case 2:
        enemy1.loadFromFile("resources/enemy3.png");
        break;
    case 3:
        enemy1.loadFromFile("resources/enemy2.png");
        break;
    default:
        enemy1.loadFromFile("resources/enemy1.png");
        break;
    }

    auto xDif = 28.f;
    if (orientation == "R")
    {
        xDif = xDif;
    }
    else
    {
        xDif = -xDif;
    }
    sf::Sprite skullEnemy1;
    skullEnemy1.setTexture(enemy1);
    skullEnemy1.setPosition(sf::Vector2f(firstXPos, yPos));
    skullEnemy1.scale(sf::Vector2f(2.5f, 2.5f));

    sf::Sprite skullEnemy2;
    skullEnemy2.setTexture(enemy1);
    skullEnemy2.setPosition(sf::Vector2f(firstXPos + xDif, yPos));
    skullEnemy2.scale(sf::Vector2f(2.5f, 2.5f));

    sf::Sprite skullEnemy5;
    skullEnemy5.setTexture(enemy1);
    skullEnemy5.setPosition(sf::Vector2f(firstXPos + 4 * xDif, yPos));
    skullEnemy5.scale(sf::Vector2f(2.5f, 2.5f));

    sf::Sprite skullEnemy3;
    skullEnemy3.setTexture(enemy1);
    skullEnemy3.setPosition(sf::Vector2f(firstXPos + 8 * xDif, yPos));
    skullEnemy3.scale(sf::Vector2f(2.5f, 2.5f));

    sf::Sprite skullEnemy4;
    skullEnemy4.setTexture(enemy1);
    skullEnemy4.setPosition(sf::Vector2f(firstXPos + 7 * xDif, yPos));
    skullEnemy4.scale(sf::Vector2f(2.5f, 2.5f));

    //    skullEnemyVec.push_back(skullEnemy1);
    skullEnemyVec.push_back(skullEnemy2);
    skullEnemyVec.push_back(skullEnemy5);
    //    skullEnemyVec.push_back(skullEnemy3);
    //skullEnemyVec.push_back(skullEnemy4);
}

void EnemyRow::update()
{

    for (auto &element : skullEnemyVec)
    {
        if (orientation == "R")
        {
            element.move(1.4f, 0.f);
            if (element.getPosition().x > 2800)
            {
                element.setPosition(firstXPos, yPos);
            }
        }
        else
        {
            element.move(-1.3f, 0.f);
            if (element.getPosition().x < -1200)
            {
                element.setPosition(firstXPos, yPos);
            }
        }
        window_ptr->draw(element);
    }
}

void EnemyRow::collision()
{

    for (auto *player_ptr : (*playerVec))
    {
        for (auto &element : skullEnemyVec)
        {
            sf::FloatRect playerBox = (player_ptr->getPlayerSprite()).getGlobalBounds();
            sf::FloatRect enemyBox = element.getGlobalBounds();

            if ((enemyBox).intersects(playerBox))
            {
                player_ptr->setAliveStatus(false);
            }
        }
    }
}
