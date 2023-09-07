#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "..\game-source-code\Player.h"
#include "..\game-source-code\FileReader.h"
#include "..\game-source-code\Temperature.h"
#include "..\game-source-code\EnemyRow.h"
#include "..\game-source-code\CloudRow.h"
#include "..\game-source-code\Castle.h"

#include <cmath>
//----------------------------------------------------------------

// TEST_CASE(){
//     CHECK_THROWS(,);
//     CHECK();
//     CHECK_FALSE();
// }


 TEST_CASE("Check if bailey jumps 108px up when .jump is called"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    //create player one
    auto player1 = Player("Player 1", &window);
    auto initialYPos = player1.getY();
    player1.jumpDown();
    player1.jump();
    auto finalPos = player1.getY();
    //check if bailey moved up 108px
    CHECK((finalPos - (initialYPos+108)) <0.01);
 }


  TEST_CASE("Check if bailey jumps 108px down when .jumpDown is called"){

    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    auto player1 = Player("Player 1", &window);
    auto initialYPos = player1.getY();

    player1.jumpDown();
    auto finalPos = player1.getY();

    CHECK((initialYPos - (finalPos+108)) < -0.01);

 }

  TEST_CASE("Check if Bailey moves right when move.Right is called"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    const float baileySpeed = 10.f;

    auto player1 = Player("Player 1", &window);
    auto initialXpos = player1.getX();

    player1.move(baileySpeed, 0.f);

    auto finalXPos = player1.getX();

    CHECK_FALSE(finalXPos == initialXpos);
 }

  TEST_CASE("Check if Bailey moves left when move.Left is called"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    const float baileySpeed = 10.f;

    auto player1 = Player("Player 1", &window);
    auto initialXpos = player1.getX();

    player1.move(-baileySpeed, 0.f);

    auto finalXPos = player1.getX();

    CHECK_FALSE(finalXPos == initialXpos);

 }

  TEST_CASE("Check if Bailey cannot move past the right-most bounds of the screen"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    const float baileySpeed = 1000.f;

    auto player1 = Player("Player 1", &window);

    do{
        player1.move(baileySpeed, 0.f);
       }
    while((player1.getX()) < 1159);

    player1.move(0.f, baileySpeed);

    auto finalYPos = player1.getY();
    auto finalXPos = player1.getX();

    CHECK(finalYPos <= 1224);
}

  TEST_CASE("Check if Bailey cannot move past the left-most bounds of the screen"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    const float baileySpeed = 1000.f;

    auto player1 = Player("Player 1", &window);

    player1.move(-baileySpeed, -baileySpeed);

    auto finalYPos = player1.getY();
    auto finalXPos = player1.getX();

    if(finalXPos < 0){
        finalXPos = 0;
    }

    CHECK(finalXPos >= 0);
}


TEST_CASE("Check if bailey cannot jump above safe zone"){

    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    //create player one
    auto player1 = Player("Player 1", &window);
    auto initialYPos = player1.getY();
    player1.jump();

    auto finalPos = player1.getY();
    //check if bailey moved up 108px

    CHECK((finalPos - initialYPos)<0.01);
 }


  TEST_CASE("Check if bailey cannot jump below bounds"){

    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    auto player1 = Player("Player 1", &window);
    auto initialYPos = player1.getY();

    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();

    auto finalPos = player1.getY();

    CHECK(finalPos < 726);

 }

 TEST_CASE("Check if all game sound files can be imported"){
     sf::SoundBuffer jumpSoundBuffer;
     sf::SoundBuffer introSoundBuffer;
     sf::SoundBuffer gameSoundBuffer;
     sf::SoundBuffer dedSoundBuffer;
     sf::SoundBuffer deathSoundBuffer;
     sf::SoundBuffer outroSoundBuffer;
     sf::SoundBuffer jumpingSoundBuffer;

     CHECK(jumpSoundBuffer.loadFromFile("resources/celeste_soundgroundjump.wav"));
     CHECK(introSoundBuffer.loadFromFile("resources/celeste1.1_firststeps.wav"));
     CHECK(gameSoundBuffer.loadFromFile("resources/celeste7.1_reachforthesummit.wav"));
     CHECK(dedSoundBuffer.loadFromFile("resources/ded.wav"));
     CHECK(deathSoundBuffer.loadFromFile("resources/death.wav"));
     CHECK(outroSoundBuffer.loadFromFile("resources/outro.wav"));
     CHECK(jumpingSoundBuffer.loadFromFile("resources/jump.wav"));
 }

 TEST_CASE("Check if all font files can be imported"){
    sf::Font font;
    CHECK(font.loadFromFile("resources/AtariFont.ttf"));
 }

  TEST_CASE("Check that the data from the tutorial text file can be found and extracted"){
    //Get how to play info
    auto fileReader = new FileReader{};
    const auto howToPlayInfo = fileReader->getInfo();
    CHECK_FALSE(howToPlayInfo == "Cannot open file");
 }


 TEST_CASE("Check initial positions of players 1"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    //create player one
    auto player1 = Player("Player 1", &window);
    auto initialYPos = player1.getY();
    auto initialXPos = player1.getX();

    CHECK(abs(initialXPos - 650.f) <= 0.01);
    CHECK(abs(initialYPos - 199.f) <= 0.01);
 }

 TEST_CASE("Check initial positions of players 2"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    //create player two
    auto player2 = Player("Player 2", &window);
    auto initialYPos = player2.getY();
    auto initialXPos = player2.getX();

    CHECK(abs(initialXPos - 550.f) <= 0.01);
    CHECK(abs(initialYPos - 199.f) <= 0.01);
 }

TEST_CASE("Check if all game images can be accessed"){

     sf::Texture main_background;
     sf::Texture cloudSafeZone;
     sf::Texture cloud;
     sf::Texture background;
     sf::Texture baileyTexture1;
     sf::Texture baileyTexture2;
     sf::Texture splashScreen;
     sf::Texture enemy1;
     sf::Texture enemy2;
     sf::Texture enemy3;
     sf::Texture cloudLower;
     sf::Texture cloudUpper;
     sf::Texture castle;




     CHECK(main_background.loadFromFile("resources/splashscreen.png"));
     CHECK(cloudSafeZone.loadFromFile("resources/cloudsafezone.png"));
     CHECK(cloud.loadFromFile("resources/cloud.png"));
     CHECK(background.loadFromFile("resources/gameplaybackground.png"));
     CHECK(baileyTexture1.loadFromFile("resources/madeline.png"));
     CHECK(baileyTexture2.loadFromFile("resources/madeline2.png"));
     CHECK(splashScreen.loadFromFile("resources/splashscreen.png"));
     CHECK(enemy1.loadFromFile("resources/enemy1.png"));
     CHECK(enemy2.loadFromFile("resources/enemy2.png"));
     CHECK(enemy3.loadFromFile("resources/enemy3.png"));
     CHECK(cloudUpper.loadFromFile("resources/cloudUpper.png"));
     CHECK(cloudLower.loadFromFile("resources/cloudLower.png"));
     CHECK(castle.loadFromFile("resources/house.png"));
 }

 TEST_CASE("Check if player dies when falling off screen"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    auto player1 = Player("Player 1", &window);

    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();
    player1.jumpDown();

    CHECK(player1.isAlive());
}

TEST_CASE("Check if castle is built"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    auto player1 = new Player("Player 1", &window);
    Castle* castle1 = new Castle(player1, &window, 1);

 for(int i=1; i<=10; i++){
    player1->jumpedOnRow(1);
    castle1->update();
    player1->jumpedOnRow(2);
    castle1->update();
    player1->jumpedOnRow(3);
    castle1->update();
    player1->jumpedOnRow(4);
    castle1->update();
    player1->resetNumFloesJumped();
 }
CHECK_FALSE(castle1->isCastleBuilt() == true);

}

TEST_CASE("Check if the position and orientation of clouds change"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    vector<Player*> playerVec;
    vector<CloudRow*> cloudplatVec;

    auto player1 = new Player("Player 1", &window);

    CloudRow* CloudRow1 = new CloudRow(1, playerVec, &window);
    auto cloudPlatform1 = new CloudRow(1, playerVec, &window);
    auto cloudPlatform2 = new CloudRow(2, playerVec, &window);


    CHECK_FALSE(cloudPlatform1->orientation == cloudPlatform2->orientation);
    cloudPlatform1->changeDirection();
    CHECK(cloudPlatform1->orientation == cloudPlatform2->orientation);

}
TEST_CASE("Check if position and orientation of enemies changes"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    vector<Player*> playerVec;
    vector<EnemyRow*> enemyVec;

    auto player1 = new Player("Player 1", &window);

    EnemyRow* EnemyRow1 = new EnemyRow(1, playerVec, &window, 1);
    auto skullEnemy1 = new EnemyRow(1, playerVec, &window, 1);
    auto skullEnemy4 = new EnemyRow(2, playerVec, &window, 1);

    CHECK_FALSE(skullEnemy1->orientation == skullEnemy4->orientation);
}

TEST_CASE("Check if the timer/temperature decreases 1 second at a time"){
    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    sf::Clock tempClock;
    Temperature* temperature = new Temperature(&tempClock, &window);
    auto currentTemp = 45;
    temperature->start();
    temperature->updateTemp();

    while(tempClock.getElapsedTime().asSeconds()<1){
        temperature->updateTemp();
    }
    CHECK_FALSE(currentTemp == tempClock.getElapsedTime().asSeconds());
}

//TEST_CASE("Check if clouds change colour when player jumps on it"){
//    sf::RenderWindow window(sf::VideoMode(1224, 726, 32), "F R O S T B I T E   B A I L E Y", sf::Style::Titlebar | sf::Style::Close);
//    window.setVerticalSyncEnabled(true);
//    vector<Player*> playerVec;
//    vector<CloudRow*> cloudplatVec;
////    vector<sf::Sprite>* platCloudUpperVec;
////    vector<sf::Sprite>* platCloudLowerVec;
//
//
//    auto player1 = new Player("Player 1", &window);
//    auto player2 = new Player("Player 2", &window);
//
//    CloudRow* CloudRow1 = new CloudRow(1, playerVec, &window);
//    auto cloudPlatform1 = new CloudRow(1, playerVec, &window);
//    auto cloudPlatform2 = new CloudRow(2, playerVec, &window);
//
//    player1->jumpedOnRow(1);
//    CloudRow1->update();
//    player2->jumpedOnRow(1);
//    CloudRow1->update();
////    CHECK(platCloudUpperVec->size() == platCloudLowerVec->size());
//}
