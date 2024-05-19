//
// Created by wince on 2024. 05. 16..
//

#include "Stepper.h"

Stepper::Stepper(float x, float y, float width, float height, float outlineThickness, float shadowSize,
                 std::map<std::string, std::map<std::string, sf::Color>> *colorThemes, sf::Font *font, int fontSize, float textShadowSize,
                 std::string *activeTheme)
                 : stepperStateR(0), stepperStateL(0), font(font), shadowSize(shadowSize), textShadowSize(textShadowSize),
colorThemes(colorThemes), activeTheme(activeTheme), themeIndex(0){

    //Creates the theme names array for the stepper from the colorThemes map
    themeNames = new std::string[colorThemes->size()];
    for (auto & colorTheme : *this->colorThemes)
    {
        themeNames[themeIndex++] = colorTheme.first;
    }

    //Sets the theme index to the active theme's index
    themeIndex = 0;
    while (themeNames[themeIndex] != *activeTheme)
        themeIndex++;

    //Initializes the stepper's background's (shape) parameters
    shape.setFillColor(colorThemes->at(*activeTheme).at("BtnIdle"));
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(sf::Vector2f(x,y));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(outlineThickness);

    //Initializes the stepper's background's parameters
    this->shadowSize = shadowSize;
    if(this->shadowSize != 0) {
        this->shadow.setSize(sf::Vector2f(width, height));
        this->shadow.setPosition(sf::Vector2f(x + shadowSize, y + shadowSize));
        this->shadow.setFillColor(this->colorThemes->at(*activeTheme).at("Shadow"));
        this->shadow.setOutlineColor(this->colorThemes->at(*activeTheme).at("Shadow"));
        this->shadow.setOutlineThickness(outlineThickness);
    }

    //Initiaizes the text's parameters
    text.setFont(*this->font);
    text.setFillColor(sf::Color::Black);
    text.setLetterSpacing(-0.2);
    text.setCharacterSize(fontSize);
    text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        this->shape.getPosition().y + this->shape.getSize().y/2 - this->text.getGlobalBounds().height/2));
    //Initializes the text's shadow's parameters
    textShadow = text;
    textShadow.setFillColor(this->colorThemes->at(*activeTheme).at("Shadow"));

    //Loads the arrow textures
    arrowSprites.loadFromFile("../../src/Resources/ArrowSprites.png");

    //Sets the left arrow's parameters
    left.setTexture(&arrowSprites);
    left.setTextureRect(sf::IntRect(0,0,12,12));
    left.setSize(sf::Vector2f(70,70));
    left.setPosition(shape.getPosition().x + 10,
            shape.getPosition().y + shape.getSize().y/2 - left.getSize().y/2);

    //Sets the right arrow's parameters
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
    //Increments the theme index if it hasn't reached the size and sets the active theme to that value
    if (themeIndex < colorThemes->size()-1)
    {
        themeIndex++;
        *activeTheme = themeNames[themeIndex];
    }
}

void Stepper::stepLeft() {
    //Decrements the theme index if it hasn't reached 0 and sets the active theme to that value
    if (themeIndex > 0)
    {
        themeIndex--;
        *activeTheme = themeNames[themeIndex];
    }
}

void Stepper::update(sf::Vector2f mousePos) {
    //Sets the text's params to the current active theme and centers its position
    text.setString(*activeTheme);
    this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        this->shape.getPosition().y + this->shape.getSize().y/2 - this->text.getGlobalBounds().height/2));
    textShadow.setString(*activeTheme);
    textShadow.setPosition(sf::Vector2f(this->text.getPosition().x + textShadowSize, this->text.getPosition().y + textShadowSize));

    //Updates the steppers color
    shape.setFillColor(colorThemes->at(*activeTheme).at("BtnIdle"));

    //Handles the right arrow button
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

    //Handles the left arrow button
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
