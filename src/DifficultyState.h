//
// Created by wince on 2024. 04. 24..
//

#ifndef SFML_NHZ_DifficultySTATE_H
#define SFML_NHZ_DifficultySTATE_H

#include "CustomDiffState.h"


class DifficultyState : public iButton{
    sf::RectangleShape backgroundColor;
    sf::RectangleShape backgroundBorder;

    std::map<std::string, Difficulty*> difficulties;
    std::map<std::string, sf::Color>* theme;

    //Functions
    /// Loads fonts from file
    void initFonts();
    /// Iitializes keybinds map
    void initKeybinds();
    /// Creates the buttons
    void initButtons();
    /// Loads difficulty presets from config file
    void initDifficulty();

public:
    /// Difficulty state constructor
    /// @param window
    /// @param supportedKeys
    /// @param states pointer to the states stack
    /// @param theme active theme
    DifficultyState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
                    std::map<std::string, sf::Color>* theme);
    virtual ~DifficultyState();

    //Functions
    /// Performs needed actions before exiting the state
    void endState();
    /// Loads the last saved game from the save file
    void loadGame();

    /// Handles the inputs
    /// @param dt
    void handleInput(const float& dt) override;
    /// Performs actions when buttons are pressed
    void handleButtons() override;
    /// Updates the state
    /// @param dt
    void update(const float& dt) override;
    /// Renders the state's elements
    /// @param target
    void render(sf::RenderTarget* target = nullptr) override;
};


#endif //SFML_NHZ_DifficultySTATE_H
