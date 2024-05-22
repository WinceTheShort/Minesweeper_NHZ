//
// Created by wince on 2024. 05. 22..
//

#ifndef BOMBCELL_H
#define BOMBCELL_H

#include "Cell.h"
#include "Board.h"

class Board;

class BombCell: public Cell{
public:
    /// Cell constructor
    /// @param spriteSheet pointer to the spritesheet texture
    /// @param x x grid cords
    /// @param y y grid cords
    /// @param gridSize
    /// @param theme active theme
    BombCell(sf::Texture* spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme);
    ~BombCell();

    void loadCell(bool revealed, bool flagged, int value) override;
    /// Reveals the bomb cell
    /// @param board pointer to parent board
    void reveal(Board* board);
    void revealIfBomb(Board* board) override;
    /// Flags the bomb cell
    /// @param board pointer to parent board
    void flag(Board* board);
};



#endif //BOMBCELL_H
