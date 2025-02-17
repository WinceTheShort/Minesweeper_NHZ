//
// Created by wince on 2024. 05. 22..
//

#ifndef BOMBCELL_H
#define BOMBCELL_H

#include "Cell.hpp"
#include "Board.hpp"

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
    ~BombCell() override;

    void loadCell(bool revealed, bool flagged, int value) override;
    /// Reveals the bomb cell
    /// @param board pointer to parent board
    void reveal(Board* board) override;
    void revealIfBomb(Board* board) override;
    /// Flags the bomb cell
    /// @param board pointer to parent board
    void flag(Board* board) override;
    /// Puts the cells value on the prodided ostream
    /// @param os
    void saveCell(std::ostream* os) override;
    int isWhat(int what) override;
};



#endif //BOMBCELL_H
