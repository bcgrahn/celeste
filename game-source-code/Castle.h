#ifndef CASTLE_H
#define CASTLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Player.h"

using namespace std;

class Castle{
    public:
        Castle(Player* player, sf::RenderWindow* window_ptr, int num);
        void update();
        tuple<float,float> getDoorPosition();
        bool isCastleBuilt();
        enum name1{P1, P2, HOMESCREENBACKGROUND, GAMEBACKGROUND, FLOE, BIRD, CRAB, FISH, CASTLE, SCORE, TEMPERATURE, DEFAULT};
    private:
        vector<string>castleImages{"resources/house1.png", "resources/house2.png", "resources/house3.png", "resources/house4.png", "resources/house4.png", "resources/house5.png", "resources/house6.png", "resources/house7.png", "resources/house8.png", "resources/house9.png", "resources/house10.png", "resources/house11.png", "resources/house12.png", "resources/house13.png", "resources/house14.png", "resources/house15.png", "resources/house16.png"};
        vector<sf::Texture>textureVec[16];
        int numCloudsJumped;
        sf::Sprite castle_;
        Player* player_;
        float doorX;
        sf::Texture castleTexture;
        sf::RenderWindow* window_ptr;
};

#endif
