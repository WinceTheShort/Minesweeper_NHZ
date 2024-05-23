//
// Created by wince on 2024. 05. 05..
//

#include "Cell.h"
#include "memtrace.h"

//CELL
Cell::Cell(sf::Texture *spriteSheet, int x, int y, float gridSize, std::map<std::string, sf::Color>* theme):
spriteSheet(spriteSheet), x(x), y(y), revealed(false), flagged(false), clicked(false), left(0), right(0), theme(theme){
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

void Cell::revealIfBomb(Board* board){}
