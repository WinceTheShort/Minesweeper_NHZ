//
// Created by wince on 2024. 04. 27..
//

#include "CustomDiffState.h"

void CustomState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void CustomState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void CustomState::initButtons() {
    this->buttons["BACK"] = new Button(40,40,150,70,10,10,theme,&font,"BACK",25);
    this->buttons["START"] = new Button(1730,40,150,70,10,10,theme,&font,"START",25);

}

void CustomState::initSliders() {
    this->sliders["COLUMNS"] = new Slider(860, 1000, 200, &font, "COLUMNS", 30, theme, 9, 155);
    this->sliders["ROWS"] = new Slider(610, 1000, 200, &font, "ROWS", 30, theme, 9, 75);
    this->sliders["BOMBS"] = new Slider(1110, 1000, 200, &font, "BOMBS", 30, theme, 10, 100);


}

CustomState::CustomState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,std::stack<State*>* states,
                         std::map<std::string, sf::Color>* theme)
                         : State(window, supportedKeys, states), iButton(), iSlider(), theme(theme){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initSliders();
    customDif = nullptr;

    //Initializes the background color's parameters
    this->backgroundColor.setFillColor(theme->at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

    //Initializes the background border's parameters
    this->backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    this->backgroundBorder.setPosition(20, 20);
    this->backgroundBorder.setOutlineColor(sf::Color::Black);
    this->backgroundBorder.setOutlineThickness(20);
    this->backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));
}

CustomState::~CustomState() {
    deleteButtons();
    deleteSliders();
    delete customDif;
}

void CustomState::endState() {

}

void CustomState::handleInput(const float &dt) {
    this->checkForQuit();
}

void CustomState::handleButtons() {
    if (this->buttons["BACK"]->isPressed())
        this->quit = true;
    if (this->buttons["START"]->isPressed()){
        customDif = new Difficulty(sliders.at("COLUMNS")->getValue(),sliders.at("ROWS")->getValue(),sliders.at("BOMBS")->getValue());
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, customDif,theme));
    }
}

void CustomState::handleSliders() {
    sliders.at("BOMBS")->changeMax(sliders.at("COLUMNS")->getValue()*sliders.at("ROWS")->getValue()*0.5);
}

void CustomState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->updateSliders();
    this->handleInput(dt);
}

void CustomState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;
    target->draw(backgroundColor);
    target->draw(backgroundBorder);

    renderButtons(target);
    renderSliders(target);

    //Debug
    //renderDebug(target);
}
