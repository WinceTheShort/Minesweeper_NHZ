//
// Created by wince on 2024. 05. 05..
//

#ifndef SFML_NHZ_CELL_H
#define SFML_NHZ_CELL_H

#include "StateInterfaces.hpp"

enum {ZERO = 0, HIDDEN = 9, BOMB = 10, FLAG = 11};

class Board;

class Cell {
protected:
    sf::RectangleShape sprite;
    sf::Texture* spriteSheet;
    int x, y;
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
    virtual void loadCell(bool revealed, bool flagged, int value) = 0;
    /// Reveals the cell
    /// @param board
    virtual void reveal(Board* board) = 0;
    /// Reveals the cell if it's a bomb
    /// @param board
    virtual void revealIfBomb(Board* board);
    /// Flags the cell
    /// @param board
    virtual void flag(Board* board) = 0;
    virtual void saveCell(std::ostream* os) = 0;
    virtual int isWhat(int what) = 0;
};


#endif //SFML_NHZ_CELL_H
