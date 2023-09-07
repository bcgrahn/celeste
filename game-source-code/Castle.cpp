#include "Castle.h"
#include <SFML/Graphics.hpp>
#include "Scale.h"
//#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

Castle::Castle(Player* player, sf::RenderWindow* window, int num){
    player_ = player;
    window_ptr = window;
    name1 type = CASTLE;
    auto scale = Scale();

    numCloudsJumped = 0;

    castleTexture.loadFromFile(castleImages[0]);

    (castle_).setTexture(castleTexture); //blank image
    if(num != 2){
       (castle_).setPosition(sf::Vector2f(830.f, 110.f));
       doorX = 1020.f;
    }
    else{
       (castle_).setPosition(sf::Vector2f(30.f, 105.f));
       doorX = 220.f;
    }

    (castle_).scale(sf::Vector2f(get<0>(scale.getScale(type)), get<0>(scale.getScale(type))));
}

void Castle::update(){
    if(numCloudsJumped != player_->getTotalCloudsJumped()){
        numCloudsJumped = player_->getTotalCloudsJumped();
        if(numCloudsJumped <= 16){
            castleTexture.loadFromFile(castleImages[numCloudsJumped]);
            (castle_).setTexture(castleTexture);
        }

    }
    (*window_ptr).draw(castle_);
}

tuple<float,float> Castle::getDoorPosition(){
 return make_tuple(doorX,199.f);
}

bool Castle::isCastleBuilt()
{
    return(numCloudsJumped >= 16);
}


