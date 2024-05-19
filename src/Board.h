//
// Created by wince on 2024. 05. 05..
//

#ifndef SFML_NHZ_BOARD_H
#define SFML_NHZ_BOARD_H

#include "Cell.h"
#include <random>

class Cell;

class Board {
    typedef std::mt19937 RNG;
    uint32_t seedVal;
    RNG rng;

    Difficulty* diff;
    sf::Texture *cellSprites;
    float gridSize;
    sf::View* view;
    bool gameOverBool, started, left;
    int goodFlag, badFlag, time;

    std::map<std::string, sf::Color>* theme;

    Cell*** boardCells; //Stores cells

    /// Iitializes the board
    void initBoard();
    /// Sets the board, populates it with bombs and creates all the num cells
    /// @param mousePos
    void setBoard(sf::Vector2i mousePos);
public:
    sf::RectangleShape boardBackground;

    /// New board constructor
    /// @param diff current difficulty
    /// @param gridSize
    /// @param view
    /// @param cellSprites pointer to the cell spritesheet texture
    /// @param theme active theme
    Board(Difficulty* diff, float gridSize, sf::View* view, sf::Texture* cellSprites,std::map<std::string, sf::Color>* theme);
    /// Load board constructor
    /// @param diff current difficulty
    /// @param gridSize
    /// @param view
    /// @param cellSprites pointer to the cell spritesheet texture
    /// @param theme active theme
    /// @param load
    Board(Difficulty* diff, float gridSize, sf::View* view, sf::Texture* cellSprites,std::map<std::string, sf::Color>* theme, bool load);
    ~Board();

    /// Returns true if win conditions are met
    /// @return bool
    bool checkWinCondition();
    /// Handles the flag action
    /// @param correct true if the flagged cell should to be flagged
    /// @return true if cell could be flagged
    bool flagged(bool correct);
    /// Handles the flag removal action
    /// @param correct true if the unflagged cell should be flagged
    void unflagged(bool correct);
    /// Checks if cell cords are within the board
    /// @param x
    /// @param y
    /// @return true if cords are valid
    bool validCoords(int x, int y){return (x >= 0 && y >= 0 && x < diff->columns && y < diff->rows) && boardCells[x][y] != nullptr;}
    /// Checks the surroundings for given type
    /// @param x
    /// @param y
    /// @param forWhat
    /// @return Returns the number of given type in the surrouning cells
    int checkSurroundings(int x, int y, int forWhat);
    /// Returns started bool
    /// @return Returns true if game is started
    bool getStarted() const {return started;}
    /// Sets the time variable, used for saving game time
    /// @param time
    void setTime(int time) {this->time = time;}
    /// Returns the time, used for loading the saved game time
    /// @return time
    int getTime() const {return time;}
    /// Returns the remaining flags, used in bomb counter which displayes this value
    /// @return remaing flags
    int getRemainigFlagNum();
    /// Saves the game to the save file
    void saveGame();
    /// Sets the game over bool
    /// @param gameOver
    void setGameOver(bool gameOver){gameOverBool = gameOver;}
    /// Returns the game over bool
    /// @return
    bool gameOver() const{return gameOverBool;}
    /// Reveals bombs, used at game over
    void revealBombs();
    /// Reveals the given cell's surroundings
    /// @param x
    /// @param y
    void revealSurroundings(int x, int y);
    /// Updates the board
    /// @param mousePosGrid
    void updateBoard(sf::Vector2i mousePosGrid);
    /// Renders the board
    /// @param target
    void drawBoard(sf::RenderTarget* target);
};


#endif //SFML_NHZ_BOARD_H
