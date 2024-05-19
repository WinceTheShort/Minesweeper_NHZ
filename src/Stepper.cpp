//
// Created by wince on 2024. 05. 16..
//

#include "Stepper.h"

Stepper::Stepper(float x, float y, float width, float height, float outlineThickness, float shadowSize,
                 std::map<std::string, std::map<std::string, sf::Color>> *colorThemes, sf::Font *font, int fontSize, float textShadowSize,
                 std::string *activeTheme)
                 : stepperStateR(0), stepperStateL(0), font(font), shadowSize(shadowSize), textShadowSize(textShadowSize), colorThemes(colorThemes), activeTheme(activeTheme){

    themeNames = new std::string[colorThemes->size()];
    themeIndex = 0;
    for (auto it = this->colorThemes->begin(); it != this->colorThemes->end(); ++it)
    {
        themeNames[themeIndex++] = it->first;
    }

    themeIndex = 0;
    while (themeNames[themeIndex] != *activeTheme)
        themeIndex++;

    shape.setFillColor(colorThemes->at(*activeTheme).at("BtnIdle"));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(outlineThickness);

    this->shadowSize = shadowSize;
    if(this->shadowSize != 0) {
        this->shadow.setSize(sf::Vector2f(width, height));
        this->shadow.setPosition(sf::Vector2f(x + shadowSize, y + shadowSize));
        this->shadow.setFillColor(this->colorThemes->at(*activeTheme).at("Shadow"));
        this->shadow.setOutlineColor(this->colorThemes->at(*activeTheme).at("Shadow"));
        this->shadow.setOutlineThickness(outlineThickness);
    }
    text.setFont(*this->font);
    text.setFillColor(sf::Color::Black);
    text.setLetterSpacing(-0.2);
    text.setCharacterSize(fontSize);
    text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        this->shape.getPosition().y + this->shape.getSize().y/2 - this->text.getGlobalBounds().height/2));
    textShadow = text;
    textShadow.setFillColor(this->colorThemes->at(*activeTheme).at("Shadow"));

    arrowSprites.loadFromFile("../../src/Resources/ArrowSprites.png");

    left.setTexture(&arrowSprites);
    left.setTextureRect(sf::IntRect(0,0,12,12));
    left.setSize(sf::Vector2f(70,70));
    left.setPosition(shape.getPosition().x + 10,
            shape.getPosition().y + shape.getSize().y/2 - left.getSize().y/2);

    right.setTexture(&arrowSprites);
    right.setTextureRect(sf::IntRect(12,0,12,12));
    right.setSize(sf::Vector2f(70,70));
    right.setPosition(shape.getPosition().x + shape.getGlobalBounds().width - 120,
                     shape.getPosition().y + shape.getSize().y/2 - right.getSize().y/2);
}

Stepper::~Stepper() {
    delete[] themeNames;
}

void Stepper::stepRight() {
    if (themeIndex < colorThemes->size()-1)
    {
        themeIndex++;
        *activeTheme = themeNames[themeIndex];
    }
}

void Stepper::stepLeft() {
    if (themeIndex > 0)
    {
        themeIndex--;
        *activeTheme = themeNames[themeIndex];
    }
}

void Stepper::update(sf::Vector2f mousePos) {
    text.setString(*activeTheme);
    this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        this->shape.getPosition().y + this->shape.getSize().y/2 - this->text.getGlobalBounds().height/2));
    textShadow.setString(*activeTheme);
    textShadow.setPosition(sf::Vector2f(this->text.getPosition().x + textShadowSize, this->text.getPosition().y + textShadowSize));

    shape.setFillColor(colorThemes->at(*activeTheme).at("BtnIdle"));

    if (this->right.getGlobalBounds().contains(mousePos)){
        right.setFillColor(colorThemes->at(*activeTheme).at("BtnActive"));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            right.setFillColor(colorThemes->at(*activeTheme).at("Shadow"));
            this->stepperStateR = 1;
        }
    } else if (stepperStateR != 1){
        right.setFillColor(colorThemes->at(*activeTheme).at("BtnHover"));
        this->stepperStateR = 0;
    }

    if (stepperStateR == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (this->right.getGlobalBounds().contains(mousePos))
        {
            right.setFillColor(colorThemes->at(*activeTheme).at("BtnActive"));
            stepRight();
            stepperStateR = 0;
        }
        else{
            right.setFillColor(colorThemes->at(*activeTheme).at("BtnHover"));
            this->stepperStateR = 0;
        }
    }

    if (this->left.getGlobalBounds().contains(mousePos)){
        left.setFillColor(colorThemes->at(*activeTheme).at("BtnActive"));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            left.setFillColor(colorThemes->at(*activeTheme).at("Shadow"));
            this->stepperStateL = 1;
        }
    } else if (stepperStateL != 1){
        left.setFillColor(colorThemes->at(*activeTheme).at("BtnHover"));
        this->stepperStateL = 0;
    }

    if (stepperStateL == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (this->left.getGlobalBounds().contains(mousePos))
        {
            left.setFillColor(colorThemes->at(*activeTheme).at("BtnActive"));
            stepLeft();
            stepperStateL = 0;
        }
        else{
            left.setFillColor(colorThemes->at(*activeTheme).at("BtnHover"));
            this->stepperStateL = 0;
        }
    }
}

void Stepper::render(sf::RenderTarget *target) {
    target->draw(shadow);
    target->draw(shape);
    target->draw(textShadow);
    target->draw(text);
    target->draw(left);
    target->draw(right);
}
