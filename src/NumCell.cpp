//
// Created by wince on 2024. 05. 22..
//

#include "NumCell.h"

NumCell::NumCell(sf::Texture *spriteSheet, int x, int y, float gridSize, int value, std::map<std::string, sf::Color>* theme)  : Cell(spriteSheet, x, y, gridSize, theme),
value(value){
    type = value;
}

NumCell::~NumCell() {

}

void NumCell::loadCell(bool revealed, bool flagged, int value){
    this->value = value;
    this->type = value;
    this->revealed = revealed;
    if (revealed)
        changeSprite(value);
    this->flagged = flagged;
    if (flagged)
        changeSprite(FLAG);
}

void NumCell::reveal(Board *board) {
    if (!revealed && !flagged){
        changeSprite(value);
        revealed = true;
    }
    /*If the num cell is revealed, satisfied (the number of flags in it's surrounings match it's value)
     * and left clicked, reveal it's surroundings*/
    else if (revealed && clicked){
        if (value == board->checkSurroundings(x, y, FLAG)){
            clicked = false;
            board->revealSurroundings(x,y);
        }
    }
}

void NumCell::flag(Board *board) {
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