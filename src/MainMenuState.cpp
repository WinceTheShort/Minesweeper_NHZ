//
// Created by wince on 2024. 04. 21..
//

#include "MainMenuState.hpp"

void MainMenuState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
}

void MainMenuState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void MainMenuState::initButtons() {
    this->buttons["PLAY"] = new Button(690,280,540,170,20,10,&this->colorThemes->at(activeTheme), &this->font,"PLAY",120,6);
    this->buttons["SCORES"] = new Button(530,740,820,170,20,10,&this->colorThemes->at(activeTheme), &this->font,"SCORES",120,6);
    this->buttons["QUIT"] = new Button(835,955,250,85,10,5,&this->colorThemes->at(activeTheme),&this->font,"QUIT",60,3);
}

void MainMenuState::initSteppers() {
    steppers["THEME"] = new Stepper(300,510,1320,170,20,10,colorThemes,&font,120,6, &activeTheme);
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states,
                             std::map<std::string, std::map<std::string, sf::Color>> *colorThemes, std::string activeTheme)
: State(window, supportedKeys, states), iButton(), iStepper(), colorThemes(colorThemes), activeTheme(activeTheme){
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->initSteppers();

    //Sets the background color's parameters
    backgroundColor.setFillColor(this->colorThemes->at(activeTheme).at("BtnActive"));
    backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

    //Sets the background border's parameters
    backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    backgroundBorder.setPosition(20, 20);
    backgroundBorder.setOutlineColor(sf::Color::Black);
    backgroundBorder.setOutlineThickness(20);
    backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));

    //Sets the title background's parameters
    titleBackground.setFillColor(this->colorThemes->at(activeTheme).at("BtnHover"));
    titleBackground.setSize(sf::Vector2f(window->getSize().x - 40, 210));
    titleBackground.setPosition(20,20);
    titleBackground.setOutlineThickness(20);
    titleBackground.setOutlineColor(sf::Color::Black);

    //Sets you title text's parameters
    titleText.setFont(font);
    titleText.setFillColor(sf::Color::Black);
    titleText.setCharacterSize(150);
    titleText.setLetterSpacing(-0.7);
    titleText.setString("Minesweeper");
    titleText.setPosition(window->getSize().x/2 - titleText.getGlobalBounds().width/2, 50);

    //Sets title text's shadow's parameters
    shadowTitleText = titleText;
    shadowTitleText.setPosition(titleText.getPosition().x+10,titleText.getPosition().y+10);
    shadowTitleText.setFillColor(this->colorThemes->at(activeTheme).at("Shadow"));
}

MainMenuState::~MainMenuState() {
    deleteButtons();
    deleteSteppers();
}

void MainMenuState::endState() {
    //Saves the last used theme
    std::ofstream ofstream("../../src/Config/activeTheme.ini");
    ofstream << activeTheme;
    ofstream.close();
}

void MainMenuState::handleInput(const float &dt) {
    this->checkForQuit();
}

void MainMenuState::handleButtons() { //Updates and handles buttons
    if (this->buttons["QUIT"]->isPressed())
        this->quit = true;
    if (this->buttons["PLAY"]->isPressed()){
        this->states->push(new DifficultyState(this->window, this->supportedKeys, this->states, &colorThemes->at(activeTheme)));
    }
}

void MainMenuState::handleSteppers() {

}

void MainMenuState::updateColors()
{
    backgroundColor.setFillColor(this->colorThemes->at(activeTheme).at("BtnActive"));
    titleBackground.setFillColor(this->colorThemes->at(activeTheme).at("BtnHover"));
    shadowTitleText.setFillColor(this->colorThemes->at(activeTheme).at("Shadow"));
    for(auto &it : this->buttons)
        it.second->changeTheme(&colorThemes->at(activeTheme));
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->updateSteppers();
    this->handleInput(dt);
    updateColors();
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target= this->window;

    target->draw(this->backgroundColor);
    target->draw(backgroundColor);
    target->draw(titleBackground);
    target->draw(backgroundBorder);
    target->draw(shadowTitleText);
    target->draw(titleText);

    this->renderButtons(target);
    this->renderSteppers(target);

#ifdef DEBUG
    renderDebug(target);
#endif
}

