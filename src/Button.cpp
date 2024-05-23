//
// Created by wince on 2024. 04. 22..
//

#include "Button.h"
#include "memtrace.h"

Button::Button(float x, float y, float width, float height,float outlineThickness, float shadowSize,
               std::map<std::string, sf::Color>* theme,
               sf::Font* font, std::string text, int fontSize, float textShadowSize,
               sf::Texture* texture, int btnId): font(font), theme(theme), btnTexture(texture){
    this->buttonState = 0;
    this->buttonStateS = "BtnIdle";

    //Initializes the buttons background's (shape) parameters
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(outlineThickness);

    //Initializes the button's shadow's parameters if its value is not 0
    this->shadowSize = shadowSize;
    if(this->shadowSize != 0){
        this->shadow.setSize(sf::Vector2f(width, height));
        this->shadow.setPosition(sf::Vector2f(x + shadowSize,y + shadowSize));
        this->shadow.setFillColor(theme->at("Shadow"));
        this->shadow.setOutlineColor(theme->at("Shadow"));
        this->shadow.setOutlineThickness(outlineThickness);
    }


    //Initializes the buttons text and its shadow if there is no texture
    if (btnTexture == nullptr){
        this->text.setFont(*this->font);
        this->text.setString(text);
        this->text.setFillColor(sf::Color::Black);
        this->text.setCharacterSize(fontSize);
        this->text.setPosition(sf::Vector2f(this->shape.getPosition().x + this->shape.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                            this->shape.getPosition().y + this->shape.getSize().y/2 - this->text.getGlobalBounds().height/2));
        textShadow = this->text;
        textShadow.setFillColor(theme->at("Shadow"));
        textShadow.setPosition(sf::Vector2f(this->text.getPosition().x + textShadowSize, this->text.getPosition().y + textShadowSize));
    } else {
        //Initializes the texture if it exists
        shape.setTexture(btnTexture);
        shape.setTextureRect(sf::IntRect(btnId*12,0,12,12));
    }


}

Button::~Button() {

}

const bool Button::isPressed() {
    if (this->buttonState == 2)
    {
        buttonState = 0;
        return true;
    }
    return false;
}



void Button::update(const sf::Vector2f mousePos) {
    //Only registers buttonpress iff its clicked and released in the buttons bounds
    if (this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonStateS = "BtnHover";
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState = 1;
            this->buttonStateS = "BtnActive";
        }
    } else if (buttonState != 1){
        this->buttonState = 0;
        this->buttonStateS = "BtnIdle";
    }

    if (buttonState == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (this->shape.getGlobalBounds().contains(mousePos))
            this->buttonState = 2;
        else{
            this->buttonState = 0;
            this->buttonStateS = "BtnIdle";
        }
    }

    //Sets the fill color to the current pressed state
    this->shape.setFillColor(this->theme->at(buttonStateS));
    textShadow.setFillColor(theme->at("Shadow"));
    this->shadow.setFillColor(theme->at("Shadow"));
    this->shadow.setOutlineColor(theme->at("Shadow"));

}

void Button::render(sf::RenderTarget *target) {
    if (this->shadowSize != 0){
        target->draw(this->shadow);
    }

    target->draw(this->shape);
    if (btnTexture == nullptr){
        target->draw(this->textShadow);
        target->draw(this->text);
    }
}

