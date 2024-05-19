//
// Created by wince on 2024. 04. 21..
//

#ifndef SFML_NHZ_MAINMENUSTATE_H
#define SFML_NHZ_MAINMENUSTATE_H

#include "DifficultyState.h"

class MainMenuState : public iButton, public iStepper{
private:
    //Variables
    sf::RectangleShape backgroundColor, backgroundBorder, titleBackground;
    sf::Text titleText, shadowTitleText;

    std::string activeTheme;
    std::map<std::string, std::map<std::string, sf::Color>> *colorThemes;

    //Functions
    /// Loads font from file
    void initFonts();
    /// Initializes keybinds map
    void initKeybinds();
    /// Creates the buttons
    void initButtons();
    /// Creates the steppers (its the thing you switch between themes with)
    void initSteppers();
public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::map<std::string,
                  std::map<std::string, sf::Color>> *colorThemes, std::string activeTheme);
    virtual ~MainMenuState();

    //Functions
    /// Performs any actions needed before exiting the state
    void endState();

    /// Handles the inputs
    /// @param dt
    void handleInput(const float& dt);
    /// Performs the actions needed when buttons are pressed
    void handleButtons();
    /// Handles steppers
    void handleSteppers();
    /// Updates all of the rendered objects color themes
    void updateColors();
    /// Updtates the state, calls other update functions
    /// @param dt
    void update(const float& dt);
    /// Renders state elements
    /// @param target
    void render(sf::RenderTarget* target = nullptr);
};


#endif //SFML_NHZ_MAINMENUSTATE_H
