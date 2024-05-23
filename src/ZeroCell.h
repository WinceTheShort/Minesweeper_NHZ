//
// Created by wince on 2024. 05. 22..
//

#ifndef ZEROCELL_H
#define ZEROCELL_H

#include "Cell.h"
#include "Board.h"

class Board;

class ZeroCell: public Cell {
public:
    /// Cell constructor
    /// @param spriteSheet pointer to the spritesheet texture
    /// @param x x grid cords
    /// @param y y grid cords
    /// @param gridSize
    /// @param theme active theme
    ZeroCell(sf::Texture* spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme);
    ~ZeroCell();

    void loadCell(bool revealed, bool flagged, int value) override;
    /// Reveals the zero cell
    /// @param board pointer to parent board
    void reveal(Board* board);
    /// Flags the zero cell
    /// @param board pointer to parent board
    void flag(Board* board);
    void saveCell(std::ostream* os) override;
    int isWhat(int what) override;
};



#endif //ZEROCELL_H
