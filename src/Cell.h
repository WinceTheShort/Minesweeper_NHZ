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
    /// Cell constructor
    /// @param spriteSheet pointer to the spritesheet texture
    /// @param x x grid cords
    /// @param y y grid cords
    /// @param gridSize
    /// @param theme active theme
    Cell(sf::Texture* spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme);
    virtual ~Cell();

    /// Returns the cell's type
    /// @return type
    int getType() const{return type;}
    /// Returns true if if the cell is flagged
    /// @return flagged
    bool getFlagged() const{return flagged;}
    /// Returns true if the cell is revealed
    /// @return revealed
    bool getRevealed() const{return revealed;}
    /// Changes texture the one at the given index
    /// @param spriteI sprite index on the sprite sheet
    void changeSprite(int spriteI);
    /// Updates the cell
    /// @param mousePos
    /// @param board
    void update(sf::Vector2i mousePos, Board* board);
    /// Renders the cell
    /// @param target
    void drawCell(sf::RenderTarget* target);
    /// Sets the cells params to the given values
    /// @param revealed
    /// @param flagged
    /// @param value
    virtual void loadCell(bool revealed, bool flagged, int value);
    /// Reveals the cell
    /// @param board
    virtual void reveal(Board* board) = 0;
    /// Flags the cell
    /// @param board
    virtual void flag(Board* board) = 0;
};

class BombCell: public Cell{
public:
    /// Cell constructor
    /// @param spriteSheet pointer to the spritesheet texture
    /// @param x x grid cords
    /// @param y y grid cords
    /// @param gridSize
    /// @param theme active theme
    BombCell(sf::Texture* spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme);
    ~BombCell() override;

    /// Reveals the bomb cell
    /// @param board pointer to parent board
    void reveal(Board* board) override;
    /// Flags the bomb cell
    /// @param board pointer to parent board
    void flag(Board* board) override;
};

class ZeroCell: public Cell {
public:
    /// Cell constructor
    /// @param spriteSheet pointer to the spritesheet texture
    /// @param x x grid cords
    /// @param y y grid cords
    /// @param gridSize
    /// @param theme active theme
    ZeroCell(sf::Texture* spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme);
    ~ZeroCell() override;

    /// Reveals the zero cell
    /// @param board pointer to parent board
    void reveal(Board* board) override;
    /// Flags the zero cell
    /// @param board pointer to parent board
    void flag(Board* board) override;
};

class NumCell: public Cell {
    int value;
public:
    /// Cell constructor
    /// @param spriteSheet pointer to the spritesheet texture
    /// @param x x grid cords
    /// @param y y grid cords
    /// @param gridSize
    /// @param value num cell value
    /// @param theme active theme
    NumCell(sf::Texture* spriteSheet, int x, int y, float gridSize, int value, std::map<std::string, sf::Color>* theme);
    ~NumCell() override;

    /// Sets the num cell's parameters to the given values
    /// @param revealed
    /// @param flagged
    /// @param value
    void loadCell(bool revealed, bool flagged, int value) override;
    /// Reveales the num cell
    /// @param board pointer to parent board
    void reveal(Board* board) override;
    /// Flags the num cell
    /// @param board pointer to parent board
    void flag(Board* board) override;
};


#endif //SFML_NHZ_CELL_H
