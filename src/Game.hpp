//
// Created by wince on 2024. 04. 21..
//

#ifndef Minesweeper_NHZ_GAME_H
#define Minesweeper_NHZ_GAME_H

#include "MainMenuState.hpp"

class Game {
    //Variables
    sf::RenderWindow* window;
    sf::Event event;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSetings;
    bool fullscreen;

    sf::Clock dtClock;          //Delta time
    float dt;

    std::stack<State*> states;  //States stack

    std::map<std::string, int> supportedKeys;

    std::string activeTheme;
    std::map<std::string, std::map<std::string, sf::Color>> colorThemes;


    //Init

    /// Initializes the game class's variables
    void initVariables();
    /// Initializes the window based on the config file
    void initWindow();
    /// Initializes the states, creates the main menu state on the states stack
    void initStates();
    /// Initializes keys map based on config file
    void initKeys();
    /// Initializes color themes map based on the files found in the themes folder
    void initThemes();

public:
    Game();
    virtual ~Game();

    //Functions
    /// Does any operations required before closing the application
    void endApp();
        //update
    /// Updates the delta time
    void updateDt();
    /// Checks events (e.g. window close)
    void updateSFMLEvents();
    /// Updates the currently active state
    void update();
        //Render
    /// Renders all game elements in active state
    void render();
        //GameLoop
    /// Runs the game loop
    void run();
};


#endif //Minesweeper_NHZ_GAME_H
