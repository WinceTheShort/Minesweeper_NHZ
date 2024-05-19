//
// Created by wince on 2024. 04. 21..
//

#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
    : window(window), supportedKeys(supportedKeys), states(states), quit(false), quitState(false){}

State::~State() {

}

bool State::getQuit() const {
    return this->quit;
}

void State::checkForQuit() {
    //Only registers keypress when the key is released
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT"))))
        quitState = 1;
    if (quitState == 1 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("QUIT"))))
        this->quit = true;
}

void State::updateMousePositions() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}






