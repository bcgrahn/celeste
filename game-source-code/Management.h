#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "CloudRow.h"
#include "EnemyRow.h"
#include "Castle.h"
#include "Temperature.h"

class Management
{
public:
    Management();
    int start();
    void gamePlayLogic();
    void keyPress();

private:
    const int gameWidth = 1224; /**< The width of the game screen */
    const int gameHeight = 726; /**< The height of the game screen */
    bool isPlaying = false;
    bool isTutorial = false;
    bool singlePlayerMode = false;
    bool doublePlayerMode = false;
    bool pause = false;
    bool dead = false;
    float yTut = 727.f;
    const float baileySpeed = 8.f;
    //Sounds
    sf::SoundBuffer introSoundBuffer;
    sf::SoundBuffer jumpSoundBuffer;
    sf::SoundBuffer gameSoundBuffer;
    sf::SoundBuffer outroSoundBuffer;
    sf::SoundBuffer deathSoundBuffer;
    sf::Sound* jumpSound;
    sf::Sound* deathSound;
    sf::Sound* introSound;
    sf::Sound* outroSound;
    sf::Sound* gameSound;
    //Create window application
    sf::RenderWindow* window;
    //Players
    vector<Player*> playerVec;
    Player* player1;
    Player* player2;
    //temperature
    sf::Text tempMessage;
    //font
    sf::Font font;
    //CloudplatForms
    vector<CloudRow*> cloudPlatVec;
    //Enemies
    vector<EnemyRow*> enemyVec;
    //vector<EnemyRow*> EnemyBirdVec;
    vector<EnemyRow*> EnemyYellowVec;
    //Castle pointers
    Castle* castle1;
    Castle* castle2;
    //Winner message
    bool win = false;
    string gameStatus = "";
     sf::Clock tempClock;
     Temperature* temperature;
    //enum for scale class
    enum name {P1, P2, HOMESCREENBACKGROUND, GAMEBACKGROUND, FLOE, BIRD, CRAB, FISH, CASTLE, SCORE, TEMPERATURE, DEFAULT};

};

#endif
