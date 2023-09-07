#include "Temperature.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;

Temperature::Temperature(sf::Clock* clock, sf::RenderWindow* win){

    // Temperature message
    font.loadFromFile("resources/AtariFont.ttf");
    tempMessage.setFont(font);
    tempMessage.setCharacterSize(25);
    tempMessage.setPosition(575.f, 10.f);
    tempMessage.setFillColor(sf::Color::White);
    window_ptr = win;
    clock_ = clock;
    pauseTemp = 45;
    currentTemp = 45;
}

void Temperature::start(){
    //countdown timer for every 1s
    (*clock_).restart();
    currentTemp = pauseTemp - static_cast<int>((*clock_).getElapsedTime().asSeconds());
    tempMessage.setString(to_string(currentTemp)+ "°C");
    stopB = false;
}

void Temperature::stop(){
    stopB = true;
    pauseTemp = pauseTemp - static_cast<int>((*clock_).getElapsedTime().asSeconds());
}

bool Temperature::isZero(){
    if(currentTemp <= 0 && !stopB){
        cout << "dead" << endl;
    }
    return (currentTemp <=0);}

void Temperature::updateTemp(){
    currentTemp = pauseTemp - static_cast<int>((*clock_).getElapsedTime().asSeconds());
    tempMessage.setString(to_string(currentTemp)+ "°C");
    window_ptr->draw(tempMessage);
}
