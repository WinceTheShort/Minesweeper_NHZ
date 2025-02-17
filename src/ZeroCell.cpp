//
// Created by wince on 2024. 05. 22..
//

#include "ZeroCell.hpp"

ZeroCell::ZeroCell(sf::Texture *spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme) : Cell(spriteSheet, x, y, gridSize, theme) {
}

ZeroCell::~ZeroCell() {

}

void ZeroCell::loadCell(bool revealed, bool flagged, int value)
{
    //Sets a cells params to the given values
    this->revealed = revealed;
    if (revealed)
        changeSprite(ZERO);
    this->flagged = flagged;
    if (flagged)
        changeSprite(FLAG);
}

void ZeroCell::reveal(Board *board) {
    if (!revealed && !flagged){
        changeSprite(ZERO);
        revealed = true;
        board->revealSurroundings(x, y);
    }
}

void ZeroCell::flag(Board *board) {
    if (flagged){
        board->unflagged(false);
        changeSprite(HIDDEN);
        flagged = false;
    } else {
        if (board->flagged(false)){
            changeSprite(FLAG);
            flagged = true;
        }
    }
}

void ZeroCell::saveCell(std::ostream* os)
{
    *os << 0;
}

int ZeroCell::isWhat(int what)
{
    return what == ZERO ? 1 : 0;
}
