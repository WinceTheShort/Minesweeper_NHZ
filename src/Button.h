//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_BUTTON_H
#define SFML_NHZ_BUTTON_H

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


class Button {
private:
    std::string buttonStateS;
    int buttonState;
    sf::RectangleShape shape;
    sf::RectangleShape shadow;
    sf::Font* font;
    sf::Text text;
    sf::Text textShadow;
    float shadowSize;
    sf::Texture* btnTexture;

    std::map<std::string, sf::Color>* theme;

public:
    /// Button constructor
    /// @param x
    /// @param y
    /// @param width
    /// @param height
    /// @param outlineThickness
    /// @param shadowSize
    /// @param theme active theme
    /// @param font
    /// @param text displayed text
    /// @param fontSize
    /// @param textShadowSize
    /// @param texture pointer to texture
    /// @param btnId texture id on spritesheet
    Button(float x, float y, float width, float height,float outlineThickness, float shadowSize = 0,
           std::map<std::string, sf::Color>* theme = nullptr,
           sf::Font* font = nullptr, std::string text = "", int fontSize = 0, float textShadowSize = 0,
           sf::Texture* texture = nullptr, int btnId =0);
    ~Button();

    //Accessors
    /// Returns true it the button is pressed
    /// @return pressed
    const bool isPressed(); //checks if button is pressed

    //Functions
    /// Changes the buttons theme to the current one
    /// @param theme
    void changeTheme(std::map<std::string, sf::Color>* theme){this->theme = theme;}
    /// Updates the button
    /// @param mousePos
    void update(sf::Vector2f mousePos);
    /// Renders the button
    /// @param target
    void render(sf::RenderTarget* target); //renders button

};


#endif //SFML_NHZ_BUTTON_H
