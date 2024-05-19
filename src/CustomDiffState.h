//
// Created by wince on 2024. 04. 27..
//

#ifndef SFML_NHZ_CUSTOMDIFFSTATE_H
#define SFML_NHZ_CUSTOMDIFFSTATE_H

#include "GameState.h"

class CustomState: public iButton, public iSlider{
    sf::RectangleShape backgroundColor;
    sf::RectangleShape backgroundBorder;
    Difficulty* customDif;

    std::map<std::string, sf::Color>* theme;

    /// Loads fonts from files
    void initFonts();
    /// Initializes the keybinds map
    void initKeybinds();
    /// Creates the buttons
    void initButtons();
    /// Creates the sliders
    void initSliders();
public:
    /// Custom state constructor
    /// @param window
    /// @param supportedKeys
    /// @param states pointer to the states stack
    /// @param theme active theme
    CustomState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
                std::map<std::string, sf::Color>* theme);
    virtual ~CustomState();

    //Functions
    /// Performs any actions neede before exiting the state
    void endState();

    /// Handles input
    /// @param dt
    void handleInput(const float& dt);
    /// Performs actions when buttons are pressed
    void handleButtons();
    /// Performs actions when sliders are used
    void handleSliders();
    /// Updates the state
    /// @param dt
    void update(const float& dt);
    /// Renders the state's elements
    /// @param target
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_CUSTOMDIFFSTATE_H
