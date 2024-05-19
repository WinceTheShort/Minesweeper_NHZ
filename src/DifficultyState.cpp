//
// Created by wince on 2024. 04. 24..
//

#include "DifficultyState.h"

void DifficultyState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void DifficultyState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void DifficultyState::initButtons() {
    this->buttons["EASY"] = new Button(760,70,400,100,20,10,theme,&font,"EASY",50);
    this->buttons["MEDIUM"] = new Button(760,240,400,100,20,10,theme,&font,"MEDIUM",50);
    this->buttons["HARD"] = new Button(760,410,400,100,20,10,theme,&font,"HARD",50);
    this->buttons["CUSTOM"] = new Button(760,580,400,100,20,10,theme,&font,"CUSTOM",50);
    this->buttons["LOAD"] = new Button(760,750,400,100,20,10,theme,&font,"LOAD",50);
    this->buttons["BACK"] = new Button(760,920,400,100,20,10,theme,&font,"BACK",50);


}

void DifficultyState::initDifficulty() {
    std::ifstream file("../../src/Config/Difficulty.ini");

    if (file.is_open()){
        std::string Diff;
        int c, r, b;
        while (file >> Diff >> c >> r >> b) {
            this->difficulties[Diff] = new Difficulty(c,r,b);
        }
        difficulties["LOAD"] = new Difficulty(1,1,1);
    }
}

//Constructor
DifficultyState::DifficultyState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states,
                                   std::map<std::string, sf::Color>* theme)
: State(window, supportedKeys, states), iButton(), theme(theme){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initDifficulty();

    //Initializes the background color's parameters
    this->backgroundColor.setFillColor(theme->at("BtnActive"));
    this->backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

    //Initializes the background borders parameters
    this->backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    this->backgroundBorder.setPosition(20, 20);
    this->backgroundBorder.setOutlineColor(sf::Color::Black);
    this->backgroundBorder.setOutlineThickness(20);
    this->backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));
}

//Destructor
DifficultyState::~DifficultyState() {
    deleteButtons();
    for (auto & difficulty : this->difficulties){
        delete difficulty.second;
    }
}

void DifficultyState::endState() {

}

void DifficultyState::handleInput(const float &dt) {
    this->checkForQuit();
}

void DifficultyState::handleButtons() { //Updates and handles buttons
    if (this->buttons["BACK"]->isPressed())
        this->quit = true;
    if (this->buttons["EASY"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("EASY"),theme));
    }
    if (this->buttons["MEDIUM"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("MEDIUM"),theme));
    }
    if (this->buttons["HARD"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("HARD"),theme));
    }
    if (this->buttons["LOAD"]->isPressed()){
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, difficulties.at("LOAD"),theme,true));
    }
    if (this->buttons["CUSTOM"]->isPressed()){
        this->states->push(new CustomState(this->window, this->supportedKeys, this->states,theme));
    }
}

void DifficultyState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->handleInput(dt);
}

void DifficultyState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;

    target->draw(backgroundColor);
    target->draw(backgroundBorder);

    this->renderButtons(target);

    //Debug
    //renderDebug(target);
}


