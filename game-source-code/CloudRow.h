#ifndef CLOUDROW_H
#define CLOUDROW_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;

class CloudRow
{
public:
    CloudRow(int rowN, vector<Player*>& players, sf::RenderWindow* window);
    void update();
    void collision();
    void changeDirection();
    void cloudsJumpedOn();
    string orientation;
private:
    int rowNum;
    sf::RenderWindow* window_ptr;
    sf::Texture cloudU;
    sf::Texture cloudL;
    sf::Texture cloudP1;
    sf::Texture cloudP2;
    sf::Texture cloudP1Lower;
    vector<sf::Sprite> platCloudUpperVec;
    vector<sf::Sprite> platCloudLowerVec;
    vector<Player*>* playerVec;
    float yPos;
    float firstXPos;

    float speed;
};

#endif
