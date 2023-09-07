#ifndef ENEMYROW_H
#define ENEMYROW_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;

class EnemyRow
{
public:
    EnemyRow(int rowE, vector<Player*>& players, sf::RenderWindow* window, int enemyId);
    void update();
    void collision();
    sf::Sprite getEnemySprite();
    float numLives = 3;
    string orientation;
private:
    int rowNum;
    sf::RenderWindow* window_ptr;
    sf::Texture enemy1;
    sf::Texture enemy2;
    sf::Texture enemy3;
    vector<sf::Sprite> skullEnemyVec;
    vector<sf::Sprite> flyingEnemyVec;
    vector<sf::Sprite> yellowEnemyVec;
    vector<Player*>* playerVec;
    float yPos;
    float firstXPos;

};
#endif // ENEMYROW_H
