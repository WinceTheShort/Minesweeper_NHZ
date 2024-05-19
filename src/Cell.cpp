//
// Created by wince on 2024. 05. 05..
//

#include "Cell.h"

//CELL
Cell::Cell(sf::Texture *spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme):
spriteSheet(spriteSheet), type(0), x(x), y(y), revealed(false), flagged(false), clicked(false), left(0), right(0), theme(theme){
    //Initializes the sprite
    sprite.setPosition(x * gridSize,y * gridSize);
    sprite.setSize(sf::Vector2f(gridSize,gridSize));
    sprite.setFillColor(theme->at("BtnIdle"));
    sprite.setTexture(spriteSheet);
    sprite.setTextureRect(sf::IntRect(9*12, 0, 12, 12));
}

Cell::~Cell() {

}

void Cell::changeSprite(int spriteI) {
    sprite.setTextureRect(sf::IntRect(spriteI*12, 0, 12, 12));
}

void Cell::update(const sf::Vector2i mousePos, Board* board) {
    //Handles left click, reveal action
    if (!flagged){
        if (mousePos.x == x && mousePos.y == y){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                left = 1;
            }
        } else if (left != 1){
            left = 0;
            clicked = false;
        }
        if (left == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (mousePos.x == x && mousePos.y == y){
                clicked = true;
                reveal(board);
            } else {
                left = 0;
                clicked = false;
            }
        }
    }

    //Handles right click, flag action
    if (!revealed){
        if (mousePos.x == x && mousePos.y == y){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                right = 1;
            }
        } else if (right != 1){
            right = 0;
        }
        if (right == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            if (mousePos.x == x && mousePos.y == y){
                flag(board);
                right = 0;
            } else {
                right = 0;
            }
        }
    }
}

void Cell::drawCell(sf::RenderTarget* target) {
    target->draw(sprite);
}

void Cell::loadCell(bool revealed, bool flagged, int value) {
    //Sets a cells params to the given values
    this->revealed = revealed;
    if (revealed)
        changeSprite(type);
    this->flagged = flagged;
    if (flagged)
        changeSprite(FLAG);
}

//BOMB
BombCell::BombCell(sf::Texture *spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme) : Cell(spriteSheet, x, y, gridSize, theme) {
    type = BOMB;
}

BombCell::~BombCell() {

}

void BombCell::reveal(Board *board) {
    if (!revealed && !flagged){
        changeSprite(BOMB);
        revealed = true;
        board->setGameOver(true);
    }
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

//ZERO
ZeroCell::ZeroCell(sf::Texture *spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme) : Cell(spriteSheet, x, y, gridSize, theme) {
    type = ZERO;
}

ZeroCell::~ZeroCell() {

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

//NUM
NumCell::NumCell(sf::Texture *spriteSheet, int x, int y, float gridSize, int value, std::map<std::string, sf::Color>* theme)  : Cell(spriteSheet, x, y, gridSize, theme),
value(value){
    type = value;
}

NumCell::~NumCell() {

}

void NumCell::loadCell(bool revealed, bool flagged, int value){
    this->value = value;
    this->revealed = revealed;
    if (revealed)
        changeSprite(type);
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