//
// Created by wince on 2024. 05. 16..
//

#ifndef SFML_NHZ_STEPPER_H
#define SFML_NHZ_STEPPER_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Stepper {
private:

    int stepperStateR, stepperStateL;
    sf::Texture arrowSprites;
    sf::RectangleShape shape, shadow, right, left;
    sf::Texture butTextures;
    sf::Font* font;
    sf::Text text;
    sf::Text textShadow;
    float shadowSize, textShadowSize;

    std::map<std::string, std::map<std::string, sf::Color>> *colorThemes;
    std::string *themeNames;
    std::string *activeTheme;

    int themeIndex;

public:
    Stepper(float x, float y, float width, float height,float outlineThickness, float shadowSize = 0,
            std::map<std::string, std::map<std::string, sf::Color>> *colorThemes = nullptr,
           sf::Font* font = nullptr, int fontSize = 0, float textShadowSize = 0,
           std::string *activeTheme = nullptr);
    ~Stepper();

    //Functions
    void changeTheme(std::map<std::string, std::map<std::string, sf::Color>> *colorThemes){this->colorThemes = colorThemes;}
    void stepRight();
    void stepLeft();
    void update(sf::Vector2f mousePos); //updates stepper
    void render(sf::RenderTarget* target); //renders stepper
};


#endif //SFML_NHZ_STEPPER_H
