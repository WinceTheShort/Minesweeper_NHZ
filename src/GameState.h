//
// Created by wince on 2024. 04. 22..
//

#ifndef SFML_NHZ_GAMESTATE_H
#define SFML_NHZ_GAMESTATE_H

#include "Board.h"


class GameState : public iButton{
private:
    //Variables
    sf::RectangleShape backgroundColor, backgroundBorder, uiBackground;
    sf::Texture buttonSprites, cellSprites;


    sf::View view;
    float viewSpeed;
    bool isShiftPressed;

    sf::Vector2i mousePosGrid;
    float gridSize;

    Difficulty *currentDifficulty;
    Board* board;
    int correctFlag, wrongFlag;
    bool gameEnded, win;

    int clock;
    sf::Clock timerClock;
    sf::Text bombCounterText, clockText, youWinText, gameOverText;
    sf::RectangleShape bombCounterIcon;

    std::map<std::string, sf::Color>* theme;

    //Functions
    /// Loads fonts from files
    void initFonts();
    /// Initializes the keybinds map
    void initKeybinds();
    /// Creates the buttons
    void initButtons();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
              Difficulty *difficulty, std::map<std::string, sf::Color>* theme, bool load = false);
    virtual ~GameState();

    //Functions
    /// Performs actions needed before exiting the state
    void endState();
    /// Checks if the end game conditions are met and sets the win and end bool accordingly
    void checkEndGameCondition();

    /// Handles inputs
    /// @param dt
    void handleInput(const float& dt);
    /// Performs actions when buttons are pressed
    void handleButtons();
    /// Updates the mouse positions
    void updateMousePositions();
    /// Updates the timer
    void updateClock();
    /// Updates the bomb counter
    void updateBombCounter();
    /// Updates the state
    /// @param dt
    void update(const float& dt);
    /// Renders the state elements to given target
    /// @param target
    void render(sf::RenderTarget* target = nullptr);    //Renders state elements, takes sf::RenderTarget*

    /// Renders the debug window
    /// @param target
    void renderDebug(sf::RenderTarget* target){
        std::stringstream ss;
        sf::Text mousePosText;
        sf::RectangleShape backdrop;
        sf::Font debugFont;

        debugFont.loadFromFile("../../src/Resources/minepixel.ttf");
        ss << "Screen: " << mousePosScreen.x << ", " << mousePosScreen.y << "\n" <<
           "Window: " << mousePosWindow.x << ", " << mousePosWindow.y << "\n" <<
           "View: " << mousePosView.x << ", " << mousePosView.y << "\n" <<
           "Grid: " << mousePosGrid.x << ", " << mousePosGrid.y << "\n" <<
           "View size: " << view.getSize().x << ", " << view.getSize().y << "\n" <<
           "View speed:" << viewSpeed << "\n" <<
           "Columns: " << currentDifficulty->columns << "\n" <<
           "Rows: " << currentDifficulty->rows << "\n" <<
           "Bombs: " << currentDifficulty->bombs << "\n";
        mousePosText.setFont(font);
        mousePosText.setString(ss.str());
        mousePosText.setPosition(sf::Vector2f(20,20));
        mousePosText.setCharacterSize(15);
        mousePosText.setFillColor(sf::Color::Black);
        backdrop.setSize(sf::Vector2f(300,200));
        backdrop.setFillColor(sf::Color(255,255,255,100));

        target->draw(backdrop);
        target->draw(mousePosText);
    }     //Renders debug panel
};


#endif //SFML_NHZ_GAMESTATE_H
