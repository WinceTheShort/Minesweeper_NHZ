//
// Created by wince on 2024. 05. 22..
//

#ifndef NUMCELL_H
#define NUMCELL_H

#include "Cell.h"
#include "Board.h"

class Board;

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
    ~NumCell();

    /// Sets the num cell's parameters to the given values
    /// @param revealed
    /// @param flagged
    /// @param value
    void loadCell(bool revealed, bool flagged, int value);
    /// Reveales the num cell
    /// @param board pointer to parent board
    void reveal(Board* board);
    /// Flags the num cell
    /// @param board pointer to parent board
    void flag(Board* board);
    void saveCell(std::ostream* os) override;
    int isWhat(int what) override;
};



#endif //NUMCELL_H
