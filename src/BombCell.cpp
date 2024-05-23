//
// Created by wince on 2024. 05. 22..
//

#include "BombCell.h"
#include "memtrace.h"

BombCell::BombCell(sf::Texture *spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme) : Cell(spriteSheet, x, y, gridSize, theme) {
}

BombCell::~BombCell() {

}

void BombCell::loadCell(bool revealed, bool flagged, int value)
{
    //Sets a cells params to the given values
    this->revealed = revealed;
    if (revealed)
        changeSprite(BOMB);
    this->flagged = flagged;
    if (flagged)
        changeSprite(FLAG);
}

void BombCell::reveal(Board *board) {
    if (!revealed && !flagged){
        changeSprite(BOMB);
        revealed = true;
        board->setGameOver(true);
    }
}

void BombCell::revealIfBomb(Board* board)
{
    reveal(board);
}

void BombCell::flag(Board *board) {
    if (flagged){
        board->unflagged(true);
        changeSprite(HIDDEN);
        flagged = false;
    } else {
        if (board->flagged(true)){
            changeSprite(FLAG);
            flagged = true;
        }
    }
}

void BombCell::saveCell(std::ostream* os)
{
    *os << 9;
}

int BombCell::isWhat(int what)
{
    return what == BOMB ? 1 : 0;
}
