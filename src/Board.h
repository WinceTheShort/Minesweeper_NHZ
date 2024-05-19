//
// Created by wince on 2024. 05. 05..
//

#ifndef SFML_NHZ_BOARD_H
#define SFML_NHZ_BOARD_H

#include "Cell.h"
#include <random>

class Cell;

class Board {
private:
    typedef std::mt19937 RNG;
    uint32_t seedVal;
    RNG rng;

    Difficulty* diff;
    sf::Texture *cellSprites;
    int gridSize;
    sf::View* view;
    bool gameOverBool, started, left;
    int goodFlag, badFlag, time;

    std::map<std::string, sf::Color>* theme;

    Cell*** boardCells; //Stores cells

    void initBoard();   //initializes board
    void setBoard(sf::Vector2i mousePos);    //sets cell values
public:
    sf::RectangleShape boardBackground;

    //New board constructor
    Board(Difficulty* diff, int gridSize, sf::View* view, sf::Texture* cellSprites,std::map<std::string, sf::Color>* theme);
    //Load board constructor
    Board(Difficulty* diff, int gridSize, sf::View* view, sf::Texture* cellSprites,std::map<std::string, sf::Color>* theme, bool load);
    ~Board();

    bool checkWinCondition();
    bool flagged(bool correct);
    void unflagged(bool correct);
    bool validCoords(int x, int y){return (x >= 0 && y >= 0 && x < diff->columns && y < diff->rows) && boardCells[x][y] != nullptr;}
    int checkSurroundings(int x, int y, int forWhat);
    bool getStarted() {return started;}
    void setTime(int time) {this->time = time;}
    int getTime() {return time;}
    int getRemainigFlagNum(); //returns remaining flag num
    void saveGame();                                    //Saves current game to a save file
    void setGameOver(bool gameOver){gameOverBool = gameOver;}
    bool gameOver(){return gameOverBool;}  //returns game over bool
    void revealSurroundings(int x, int y);
    void updateBoard(sf::Vector2i mousePosGrid);
    void drawBoard(sf::RenderTarget* target);   //renders the board, takes sf::RenderTarget*
};


#endif //SFML_NHZ_BOARD_H
