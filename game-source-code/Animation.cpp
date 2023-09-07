#include "Animation.h"
#include <iostream>

using namespace std;

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount_, float switchTime_, sf::IntRect* textureSprite)
{
    // Num images
    imageCount = imageCount_;
    textureRect = textureSprite;
    // Delay/switch time
    switchTime = switchTime_;

    totalTime = 0.0f;
    // 2d vector of current image positon (x,y)
    currentImage.x = 0.0f;
    // spritesheet texture
    textureRect->width = texture->getSize().x / float(imageCount.x);
    textureRect->height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        cout << "here" << endl;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

    textureRect->left = currentImage.x * textureRect->width;
    textureRect->top = currentImage.y * textureRect->height;
}
