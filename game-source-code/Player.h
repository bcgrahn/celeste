#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Animation.h"

using namespace std;

class Player
{
public:
    Player(string playerID, sf::RenderWindow* window);
    bool isAlive();
    void jumpedOnRow(int rowNumber);
    int onWhatRow();
    void addPoints();
    bool landedOnAllRows();
    bool inSafeZone();
    bool onIceFloe(bool status);
    void resetNumFloesJumped();
    void decreaseNumFloesJumped();
    void jump();
    void jumpDown();
    float getY();
    float getX();
    float xScore;
    void update();
    void move(float x, float y);
    bool isFalling();
    int getTotalCloudsJumped();
    sf::Sprite getPlayerSprite();
    void setAliveStatus(bool stat);
    vector<bool> getRowsJumpedOn();
    int getPlayerID();
    bool playerAtCastleEntrance(int cX, int cY);
private:
    char status;
    int scorePts;
    int count = 0;
    bool isAliveState = true;
    bool jumpDownFinished = true;
    bool jumpUpFinished = true;
    int lives = 1;
    int numFloesJumpedOn = 0;
    bool onCloud = false;
    bool isFallingBool = false;
    int onCurrentRow;
    sf::Sprite player;
    sf::Text score;
    sf::Font font;
    sf::Texture baileyTexture;
    Animation* play1Animation;
    Animation* play2Animation;

    sf::IntRect rectSourceSprite;
    float deltaTime;
    // Movement clock for timing
    sf::Clock clockTime;
    vector<bool>rowsJumpedOn;
    sf::RenderWindow* window_ptr;
    int playerIdentity;
    enum name {P1, P2, HOMESCREENBACKGROUND, GAMEBACKGROUND, FLOE, BIRD, CRAB, FISH, CASTLE, SCORE, TEMPERATURE, DEFAULT};
};

#endif
