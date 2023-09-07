#include "Management.h"
#include "Player.h"
#include "FileReader.h"
#include "Scale.h"
#include "CloudRow.h"
#include "EnemyRow.h"
#include "Castle.h"
#include "Temperature.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <tuple>

using namespace std;

Management::Management()
{
    // Declare and initialize
    isPlaying = false;
    isTutorial = false;
    singlePlayerMode = false;
    doublePlayerMode = false;
    pause = false;
    yTut = 727.f;

    // Insert game sounds
    if (!jumpSoundBuffer.loadFromFile("resources/jump.wav"))
    {
        cout << "could not locate the jump sound" << endl;
    }
    jumpSound = new sf::Sound(jumpSoundBuffer);
    jumpSound->setVolume(25.f);

    if (!introSoundBuffer.loadFromFile("resources/celeste1.1_firststeps.wav"))
    {
        cout << "could not locate the intro sound" << endl;
    }
    introSound = new sf::Sound(introSoundBuffer);
    introSound->setVolume(20.f);

    if (!outroSoundBuffer.loadFromFile("resources/outro.wav"))
    {
        cout << "could not locate the outro sound" << endl;
    }
    outroSound = new sf::Sound(outroSoundBuffer);
    outroSound->setVolume(35.f);

    if (!gameSoundBuffer.loadFromFile("resources/celeste7.1_reachforthesummit.wav"))
    {
        cout << "could not locate the gamePlay sound" << endl;
    }
    gameSound = new sf::Sound(gameSoundBuffer);

    if (!deathSoundBuffer.loadFromFile("resources/ded.wav"))
    {
        cout << "could not locate the death sound" << endl;
    }
    deathSound = new sf::Sound(deathSoundBuffer);
    deathSound->setVolume(70.f);

    // Game window
    window = new sf::RenderWindow(sf::VideoMode(gameWidth, gameHeight, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);

    // Game font
    if (!font.loadFromFile("resources/AtariFont.ttf"))
        cout << "could not locate font" << endl;

    // create player one
    player1 = new Player("Player 1", window);

    // create player Two
    player2 = new Player("Player 2", window);

    // Castle pointer
    castle1 = new Castle(player1, window, 1);
    castle2 = new Castle(player2, window, 2);

}

int Management::start()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    bool winSoundPlay = false;
    bool deadSoundPlay = false;

    // Dead message
    sf::Text deadM;
    deadM.setFont(font);
    deadM.setCharacterSize(20);
    deadM.setPosition(450.f, 350.f);
    deadM.setFillColor(sf::Color::White);
    deadM.setString("You have died");

    // Create window application
    window->setVerticalSyncEnabled(true);

    // Insert mainbackground
    sf::Texture main_background;
    if (!main_background.loadFromFile("resources/splashscreen.png"))
    {
        // cout << "could not locate the background image" << endl;
    }
    sf::Sprite backsprite;
    backsprite.setTexture(main_background);
    backsprite.setPosition(sf::Vector2f(0.f, 0.f));
    backsprite.scale(sf::Vector2f(3.85f, 4.1f));
    window->draw(backsprite);

    // Insert cloud safezone
    sf::Texture cloudSafeZone;
    if (!cloudSafeZone.loadFromFile("resources/cloudsafezone.png"))
    {
        // cout << "could not locate the cloud safe zone image" << endl;
    }
    sf::Sprite safeCloud;
    safeCloud.setTexture(cloudSafeZone);
    safeCloud.setPosition(sf::Vector2f(0.f, 142.f));
    safeCloud.scale(sf::Vector2f(4.5f, 4.5f));

    // Vector of players
    playerVec.push_back(player1);

    // Vector of cloud platforms
    auto cloudPlatform1 = new CloudRow(1, playerVec, window);
    auto cloudPlatform2 = new CloudRow(2, playerVec, window);
    auto cloudPlatform3 = new CloudRow(3, playerVec, window);
    auto cloudPlatform4 = new CloudRow(4, playerVec, window);

    cloudPlatVec.push_back(cloudPlatform1);
    cloudPlatVec.push_back(cloudPlatform2);
    cloudPlatVec.push_back(cloudPlatform3);
    cloudPlatVec.push_back(cloudPlatform4);

    // Vector of skull enemies
    auto skullEnemy1 = new EnemyRow(1, playerVec, window, 1);
    auto skullEnemy4 = new EnemyRow(4, playerVec, window, 1);
    auto birdEnemy2 = new EnemyRow(2, playerVec, window, 2);
    auto birdEnemy3 = new EnemyRow(3, playerVec, window, 2);
    enemyVec.push_back(skullEnemy1);
    enemyVec.push_back(skullEnemy4);
    enemyVec.push_back(birdEnemy2);
    enemyVec.push_back(birdEnemy3);

    // Insert game background
    sf::Texture background;
    if (!background.loadFromFile("resources/gameplaybackground.png"))
    {
        // cout << "could not locate the background image" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(background);
    sprite.setPosition(sf::Vector2f(0.f, 0.f));
    sprite.scale(sf::Vector2f(1.23f, 1.09f));

    // Load the text font

    // Title Text
    sf::Text Title;
    Title.setFont(font);
    Title.setCharacterSize(18);
    Title.setPosition(325.f, 150.f);
    Title.setFillColor(sf::Color::White);
    Title.setString("");

    // Title Text
    sf::Text winnerMessage;
    winnerMessage.setFont(font);
    winnerMessage.setCharacterSize(18);
    winnerMessage.setPosition(400.f, 346.f);
    winnerMessage.setFillColor(sf::Color::White);
    winnerMessage.setString("");

    // Controls message
    sf::Text controlsM;
    controlsM.setFont(font);
    controlsM.setCharacterSize(13);
    controlsM.setPosition(440.f, 150.f);
    controlsM.setFillColor(sf::Color::White);
    controlsM.setString("GAME MODE\n---------\n\n[G] Press G for single player\n\n\[H] or H to play with a friend\n\n\n\n\n\n\n\n\n\n\n\n\nCONTROLS\n---------\n\n[W/Up Arrow] To Jump up\n\n[S/Down Arrow] To Jump down\n\n[A/Left Arrow] To move left\n\n[D/Right arrow] To Jump right\n\n[P] To pause/unpause\n\n[Q/M] To reverse direction \n       of clouds");

    // Game message
    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(13);
    message.setPosition(430.f, 400.f);
    message.setFillColor(sf::Color::White);
    message.setString("[Space] Press space to start\n        the game\n\n[Esc] Esc to exit\n\n[B] B to go back\n\n[T] T for how to play");

    // Pause message
    sf::Text pauseM;
    pauseM.setFont(font);
    pauseM.setCharacterSize(20);
    pauseM.setPosition(410.f, 350.f);
    pauseM.setFillColor(sf::Color::White);
    pauseM.setString("Press p to resume :)");

    // Get how to play info
    auto fileReader = new FileReader{};
    const auto howToPlayInfo = fileReader->getInfo();

    // HowToPlay scrollable info
    const int SCROLL_SPEED = 20; // 20 pixels per second
    sf::Text howTo;
    howTo.setFont(font);
    howTo.setCharacterSize(17);
    howTo.setPosition(120.f, yTut);
    howTo.setFillColor(sf::Color::White);
    howTo.setString(howToPlayInfo);

    // create scale object for easy retrieval of scales for adjusting sprite proportions
    auto scale = Scale();
    auto spriteName = DEFAULT;
    auto xS = get<0>(scale.getScale(spriteName));
    auto yS = get<1>(scale.getScale(spriteName));

    // Movement clock for timing
    sf::Clock clock1;
    sf::Clock clock2;
    sf::Clock clock3;

    //Temperature temperature;
    temperature = new Temperature(&tempClock, window);

    window->display();

    // Play intro sound
    introSound->play();

    // Exit on window close
    while (window->isOpen()) // or game over
    {
        // Poll for keyPress
        keyPress();
        window->clear();

        if ((isPlaying == true) && (isTutorial == false) && (!temperature->isZero()))
        {
            isTutorial = false;
            if (singlePlayerMode || doublePlayerMode)
            {

                if (!pause)
                {
                    window->draw(sprite);
                    temperature->updateTemp();
                    // Only drawing the castle here so that the castle is displayed behind the safezone clouds
                    castle1->update();
                    if (doublePlayerMode)
                    {
                        castle2->update();
                    }
                    window->draw(safeCloud);

                    // Game Play Logic
                    gamePlayLogic();
                }
                else
                {
                    //temperature->stop();
                    window->draw(pauseM);
                }
            }
            else
            {
                window->draw(backsprite);
                window->draw(controlsM);
            }
        }
        else if (isTutorial)
        {
            // Display tutorial information
            howTo.setPosition(30.f, --yTut);
            window->draw(backsprite);
            window->draw(howTo);
        }
        else if (dead)
        {
            window->clear();
            if(!deadSoundPlay){
                deathSound->play();
                deadSoundPlay = true;
            }
            window->draw(deadM);
            gameSound->stop();
        }
        else if (win == true)
        {
            window->clear();
            if(!winSoundPlay){
                outroSound->play();
                winSoundPlay = true;
            }

            winnerMessage.setString(gameStatus);
            gameSound->stop();
            window->draw(winnerMessage);
        }
        else if (isPlaying == false)
        {
            window->draw(backsprite);
            window->draw(Title);
            window->draw(message);
        }
        else if (temperature->isZero())
        {
            window->draw(deadM);
        }

        // Refresh window
        window->display();
    }

    return 0;
}

void Management::gamePlayLogic()
{

    for (auto element : cloudPlatVec)
    {
        element->update();
    }
    for (auto element : enemyVec)

    {
        element->update();
    }

    if(player1->isAlive())
    {
        player1->move(0,0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player1->move(baileySpeed, 0.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player1->move(-baileySpeed, 0.f);
        }

        player1->update();
    }

    if (doublePlayerMode)
    {

        if(player2->isAlive())
        {
            player2->move(0,0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player2->move(baileySpeed, 0.f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player2->move(-baileySpeed, 0.f);
            }

            player2->update();
        }

    }

    for (auto *element : playerVec)
    {
        element->onIceFloe(false);
    }

    for (auto *element : cloudPlatVec)
    {
        element->collision();
    }

    if (castle1->isCastleBuilt() || castle2->isCastleBuilt())
    {
        int cX = get<0>(castle1->getDoorPosition());
        int cY = get<1>(castle1->getDoorPosition());
        player1->playerAtCastleEntrance(cX, cY);

        if (player1->playerAtCastleEntrance(cX, cY))
        {
            gameStatus = "Player 1 is the WINNER!!!!";
            win = true;
            isPlaying = false;
        }

        if (playerVec.size() > 1)
        {
            int cX = get<0>(castle2->getDoorPosition());
            int cY = get<1>(castle2->getDoorPosition());
            player2->playerAtCastleEntrance(cX, cY);

            if (player2->playerAtCastleEntrance(cX, cY))
            {
                win = true;
                gameStatus = "Player 2 is the WINNER!!!!";
                isPlaying = false;
            }
        }
    }

    for (auto *element : enemyVec)
    {
        element->collision();
    }

    if (player1->isAlive() == false)
    {
        if (playerVec.size() > 1)
        {
            if (player2->isAlive() == false)
            {
                dead = true;
                deathSound->play();
                isPlaying = false;
            }
        }
        else
        {
            deathSound->play();
            dead = true;
            isPlaying = false;
        }
    }
}

void Management::keyPress()
{
    sf::Event event;

    // executes while there is an event
    while (window->pollEvent(event))
    {
        if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
        {
            window->close();
            break;
        }

        if (!pause && isPlaying)
        {
            if(player1->isAlive())
            {
                // Continuous y movement for player 1
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down) && (player1->getY() <= gameHeight - 130))
                {
                    jumpSound->play();
                    player1->jumpDown();
                    player1->jumpedOnRow(-1);
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up) && (player1->getY() >= 220))
                {
                    jumpSound->play();
                    player1->jump();
                    player1->jumpedOnRow(-1);
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::M))
                {
                    int rowOn = player1->onWhatRow();
                    if (rowOn != -1)
                    {
                        cloudPlatVec[rowOn - 1]->changeDirection();
                        player1->decreaseNumFloesJumped();
                    }
                }

            }

            if (doublePlayerMode)
            {
                if(player2->isAlive())
                {
                    // Continuous y movement for player 2
                    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S) && (player2->getY() <= gameHeight - 130))
                    {
                        jumpSound->play();
                        player2->jumpDown();
                        player2->jumpedOnRow(-1);
                    }
                    else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W) && (player2->getY() >= 220))
                    {
                        jumpSound->play();
                        player2->jump();
                        player2->jumpedOnRow(-1);
                    }
                    else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Q))
                    {
                        int rowOn = player2->onWhatRow();
                        if (rowOn > 0)
                        {
                            cloudPlatVec[rowOn - 1]->changeDirection();
                            player2->decreaseNumFloesJumped();
                        }
                    }
                }

            }
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
        {
            if (!isPlaying)
            {
                isPlaying = true;
                cout << "[1] Game has begun" << endl;
                break;
            }
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::T))
        {
            if (!isPlaying)
            {
                isTutorial = true;
                break;
            }
        }

        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::B) && !(singlePlayerMode || doublePlayerMode))
        {
            isTutorial = false;
            isPlaying = false;
            singlePlayerMode = false;
            doublePlayerMode = false;
            yTut = 726.f;
            break;
        }

        if (!singlePlayerMode && !doublePlayerMode && isPlaying)
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::G))
            {
                introSound->stop();
                gameSound->play();
                gameSound->setVolume(18.f);
                isTutorial = false;
                isPlaying = true;
                singlePlayerMode = true;
                doublePlayerMode = false;
                tempClock.restart();
                break;
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::H))
            {
                playerVec.push_back(player2);
                introSound->stop();
                gameSound->play();
                gameSound->setVolume(18.f);
                isTutorial = false;
                isPlaying = true;
                singlePlayerMode = true;
                doublePlayerMode = true;
                tempClock.restart();
                break;
            }
        }
        else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P))
        {
            pause = !pause;

            if (pause)
            {
                gameSound->pause();
                temperature->stop();
            }
            else
            {
                gameSound->play();
                temperature->start();
            }

            break;
        }
    }
}
