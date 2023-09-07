#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <SFML/Graphics.hpp>
#include <ctime>

class Temperature
{
public:
    Temperature(sf::Clock* clock, sf:: RenderWindow* win);
    void start();
    void stop();
    bool isZero();
    void updateTemp();

private:
    int pauseTemp;
    sf::Clock* clock_;
    int currentTemp;
    sf::Text tempMessage;
    sf::RenderWindow* window_ptr;
    sf::Font font;
    bool stopB = false;
};

#endif
