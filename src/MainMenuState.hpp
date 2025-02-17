//
// Created by wince on 2024. 04. 21..
//

#ifndef Minesweeper_NHZ_MAINMENUSTATE_H
#define Minesweeper_NHZ_MAINMENUSTATE_H

#include "DifficultyState.hpp"

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
    void initKeybinds() override;
    /// Creates the buttons
    void initButtons() override;
    /// Creates the steppers (its the thing you switch between themes with)
    void initSteppers() override;
public:
    /// Main menu state constructor
    /// @param window
    /// @param supportedKeys
    /// @param states pointer to the states stack
    /// @param colorThemes pointer to the color themes map
    /// @param activeTheme the name of the active theme
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::map<std::string,
                                                                                                                            std::map<std::string, sf::Color>> *colorThemes, std::string activeTheme);
    ~MainMenuState() override;

    //Functions
    /// Performs any actions needed before exiting the state
    void endState() override;

    /// Handles the inputs
    /// @param dt
    void handleInput(const float& dt) override;
    /// Performs the actions needed when buttons are pressed
    void handleButtons() override;
    /// Handles steppers
    void handleSteppers() override;
    /// Updates all of the rendered objects color themes
    void updateColors();
    /// Updtates the state, calls other update functions
    /// @param dt
    void update(const float& dt) override;
    /// Renders state elements
    /// @param target
    void render(sf::RenderTarget* target = nullptr) override;
};


#endif //Minesweeper_NHZ_MAINMENUSTATE_H
