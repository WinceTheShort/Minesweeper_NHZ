//
// Created by wince on 2024. 05. 05..
//

#ifndef SFML_NHZ_CELL_H
#define SFML_NHZ_CELL_H

#include "StateInterfaces.hpp"
#include "Board.h"

enum {ZERO = 0, HIDDEN = 9, BOMB = 10, FLAG = 11};

class Board;

class Cell {
protected:
    sf::RectangleShape sprite;
    sf::Texture* spriteSheet;
    int type, x, y;
    bool revealed, flagged, clicked;
    int left, right;

    std::map<std::string, sf::Color>* theme;


public:
    Cell(sf::Texture* spriteSheet, int x, int y, int gridSize, std::map<std::string, sf::Color>* theme);
    ~Cell();

    int getType(){return type;}
    bool getFlagged(){return flagged;}
    bool getRevealed(){return revealed;}
    void changeSprite(int spriteI); //Changes tiles sprite, takes the index of sprite
    void update(const sf::Vector2i mousePos, Board* board);
    void drawCell(sf::RenderTarget* target);
    virtual void loadCell(bool revealed, bool flagged, int value);
    virtual void reveal(Board* board) = 0;  //reveals the cell
    virtual void flag(Board* board) = 0;    //handles flag numbers
};

class BombCell: public Cell{
private:
public:
    BombCell(sf::Texture* spriteSheet, int x, int y, int gridSize, std::map<std::string, sf::Color>* theme);
    ~BombCell();

    void reveal(Board* board);
    void flag(Board* board);
};

class ZeroCell: public Cell {
private:
public:
    ZeroCell(sf::Texture* spriteSheet, int x, int y, int gridSize, std::map<std::string, sf::Color>* theme);
    ~ZeroCell();

    void reveal(Board* board);
    void flag(Board* board);
};

class NumCell: public Cell {
private:
    int value;
public:
    NumCell(sf::Texture* spriteSheet, int x, int y, int gridSize, int value, std::map<std::string, sf::Color>* theme);
    ~NumCell();

    void loadCell(bool revealed, bool flagged, int value);
    void reveal(Board* board);
    void flag(Board* board);
};


#endif //SFML_NHZ_CELL_H
