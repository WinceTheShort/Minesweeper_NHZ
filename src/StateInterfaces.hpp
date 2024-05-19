//
// Created by Vince on 2024. 04. 30..
//

#ifndef SFML_NHZ_STATEINTERFACES_HPP
#define SFML_NHZ_STATEINTERFACES_HPP

#include "State.h"

//Button interface
class iButton: virtual public State{
protected:
    std::map<std::string, Button*> buttons;
public:
    virtual void initButtons() = 0; //initializes buttons
    virtual void handleButtons() = 0; //handles buttons

    /// Calls the all of the existing buttons' update function
    void updateButtons(){
        for(auto &it : this->buttons)
            it.second->update(sf::Vector2f(this->mousePosWindow.x, this->mousePosWindow.y));
        handleButtons();
    }

    /// Calls the all of the existing buttons' update function
    /// @param target
    void renderButtons(sf::RenderTarget *target) {
        for(auto &it : this->buttons)
            it.second->render(target);
    }

    /// Deletes the allocated buttons
    void deleteButtons(){
        auto it = this->buttons.begin();
        for (it = this->buttons.begin(); it != this->buttons.end(); ++it){
            delete it->second;
        }
    }
};

//Slider interface
class iSlider: virtual public State{
protected:
    std::map<std::string, Slider*> sliders;
public:
    virtual void initSliders() = 0; //initializes slider
    virtual void handleSliders() = 0; //handles sliders

    /// Calls all of the existing sliers' update funtions
    void updateSliders() {
        for(auto &it : this->sliders)
            it.second->update(this->mousePosView);
        handleSliders();
    }

    /// Calls all of the existing sliders' render funtions
    /// @param target
    void renderSliders(sf::RenderTarget *target) {
        for(auto &it : this->sliders)
            it.second->render(target);
    }

    /// Deletes the allocated sliders
    void deleteSliders(){
        auto it = this->sliders.begin();
        for (it = this->sliders.begin(); it != this->sliders.end(); ++it){
            delete it->second;
        }
    }
};

//Stepper interface
class iStepper: virtual public State{
protected:
    std::map<std::string, Stepper*> steppers;
public:
    virtual void initSteppers() = 0; //Initializes the steppers
    virtual void handleSteppers() = 0; //Handles the steppers
    /// Calls all of the existing steppers update functions
    void updateSteppers(){
        for(auto &it : this->steppers)
            it.second->update(this->mousePosView);
        handleSteppers();
    }

    /// Calls all of the existing steppers render functions
    /// @param target
    void renderSteppers(sf::RenderTarget *target){
        for(auto &it : this->steppers)
            it.second->render(target);
    }

    /// Deleste the allocated steppers
    void deleteSteppers(){
        auto it = this->steppers.begin();
        for (it = this->steppers.begin(); it != this->steppers.end(); ++it){
            delete it->second;
        }
    }
};


//Stores the games parameters
class Difficulty{
public:
    int columns, rows, bombs;
    Difficulty(int columns, int rows, int bombs):
    columns(columns), rows(rows), bombs(bombs){}
};


#endif //SFML_NHZ_STATEINTERFACES_HPP
