//
// Created by wince on 2024. 04. 26..
//

#ifndef SFML_NHZ_SLIDER_H
#define SFML_NHZ_SLIDER_H

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


class Slider {
private:
    sf::RectangleShape area;
    sf::RectangleShape slider;
    sf::Font* font;
    sf::Text text;
    sf::Text valueDisplay;
    int value, min, max;
    std::stringstream ss;
    float sliderMaxX;
    int sliderState;

    std::map<std::string, sf::Color>* theme;
public:
    ///
    /// @param x
    /// @param y
    /// @param width
    /// @param font
    /// @param text String displayed above the slider
    /// @param fontSize
    /// @param theme
    /// @param min min value
    /// @param max max value
    /// @param scale
    Slider(float x, float y, float width,
           sf::Font* font, const std::string& text, int fontSize,
           std::map<std::string, sf::Color>* theme,
           int min, int max, float scale = 1);
    ~Slider();

    /// Returns the sliders current value
    /// @return value
    int getValue() const; //returns sliders current value

    /// Changes the slider's theme
    /// @param theme
    void changeTheme(std::map<std::string, sf::Color>* theme){this->theme = theme;}
    /// Changes the maximum value
    /// @param newMax
    void changeMax(int newMax);
    /// Updates the slider
    /// @param mousePos
    void update(sf::Vector2f mousePos);
    /// Renders the slider
    /// @param target
    void render(sf::RenderTarget* target);
};


#endif //SFML_NHZ_SLIDER_H
