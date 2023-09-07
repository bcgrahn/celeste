#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;

public:
    sf::IntRect* textureRect;

    Animation(sf::Texture *texture, sf::Vector2u imageCount_, float switchTime_, sf::IntRect* textureSprite);
    virtual ~Animation();

    void update(int row, float deltaTime);
};

#endif // ANIMATION_H
