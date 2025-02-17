//
// Created by wince on 2024. 04. 26..
//

#include <cmath>
#include "Slider.hpp"

Slider::Slider(float x, float y, float width, sf::Font *font, const std::string& text, int fontSize,
               std::map<std::string, sf::Color> *theme, int min, int max, float scale)
                   : theme(theme), font(font), min(min), max(max), sliderState(0), value(0){

    //Initializes the slider's background's parameters
    area.setPosition(sf::Vector2f(x, y));
    area.setSize(sf::Vector2f(width, 10 * scale));
    area.setOutlineThickness(5);
    area.setOutlineColor(sf::Color::Black);
    area.setFillColor(theme->at("BtnIdle"));

    //Initializes the slider's parameters
    slider.setPosition(sf::Vector2f(x, y - (20 * scale - 10 * scale)/2));
    slider.setSize(sf::Vector2f(10*scale,20 * scale));
    slider.setOutlineColor(sf::Color::Black);
    slider.setOutlineThickness(5);
    sliderMaxX = x + width - 10 * scale;

    //Initializes the text's parameters
    this->text.setFont(*font);
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(sf::Color::Black);
    this->text.setString(text);
    this->text.setPosition(sf::Vector2f(area.getPosition().x + area.getSize().x/2 - this->text.getGlobalBounds().width/2,
                                        slider.getPosition().y - this->text.getGlobalBounds().height - 10));
    //Initializes the value display's parameters
    valueDisplay.setFont(*font);
    valueDisplay.setCharacterSize(fontSize);
    valueDisplay.setFillColor(sf::Color::Black);
}

Slider::~Slider() {

}

int Slider::getValue() const {
    return value;
}

void Slider::changeMax(int newMax) {
    max = newMax;
}

void Slider::update(sf::Vector2f mousePos) {
    //Puts the slider at the clicked pos
    if (area.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        slider.setPosition(mousePos.x - 5, slider.getPosition().y);

    //Similarly to the button, if the slider is clicked it only deactivates if left click is released
    if (slider.getGlobalBounds().contains(mousePos)){
        slider.setFillColor(theme->at("BtnActive"));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            slider.setFillColor(theme->at("Shadow"));
            sliderState = 1;
            }
    } else if (sliderState != 1)
        slider.setFillColor(theme->at("BtnHover"));

    if(sliderState == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(this->slider.getGlobalBounds().contains(mousePos)){
            slider.setFillColor(theme->at("BtnActive"));
            sliderState = 0;
        } else {
            slider.setFillColor(theme->at("BtnHover"));
            sliderState = 0;
        }
    }

    //Changes the slider's position when its active
    if (sliderState == 1){
        if (mousePos.x - 5 > area.getPosition().x && mousePos.x < sliderMaxX + 5)
            slider.setPosition(mousePos.x - 5, slider.getPosition().y);
        else if (mousePos.x - 5 < area.getPosition().x)
            slider.setPosition(area.getPosition().x, slider.getPosition().y);
        else if (mousePos.x > sliderMaxX + 5)
            slider.setPosition(sliderMaxX, slider.getPosition().y);
    }

    //Sets the value of th slider based on its relative position
    value = std::round(min + (slider.getPosition().x - area.getPosition().x) / (sliderMaxX - area.getPosition().x) * (max - min));

    //Sets the value display's string
    ss.str(std::string());
    ss << value;
    valueDisplay.setString(ss.str());
    this->valueDisplay.setPosition(sf::Vector2f(area.getPosition().x + area.getSize().x/2 - this->valueDisplay.getGlobalBounds().width/2,
                                        slider.getPosition().y + slider.getSize().y + 10));
}

void Slider::render(sf::RenderTarget *target) {
    target->draw(area);
    target->draw(slider);
    target->draw(text);
    target->draw(valueDisplay);;
}

