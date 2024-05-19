//
// Created by wince on 2024. 04. 21.
//

#ifndef SFML_NHZ_STATE_H
#define SFML_NHZ_STATE_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <filesystem>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include "Button.h"
#include "Slider.h"
#include "Stepper.h"

#include "memtrace.h"

class State {
protected:
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    sf::Font font;

    int quitState;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::vector<sf::Texture*> textures;


    //Functions
    /// Initializes keybinds map
    virtual void initKeybinds() = 0;


public:
    /// State constructor
    /// @param window
    /// @param supportedKeys
    /// @param states pointer to the states stack
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    /// Returns the quit bools value
    /// @return quit
    bool getQuit() const;

    /// Ckecks if user hit the quit keybind and sets the quit boolean accordingly
    virtual void checkForQuit();

    /// Performs any actions needed before exiting the state
    virtual void endState() = 0;
    /// Updates the mouse positions
    virtual void updateMousePositions();
    /// Handels inputs
    /// @param dt
    virtual void handleInput(const float& dt) = 0;
    /// Updates the state
    /// @param dt
    virtual void update(const float& dt) = 0;
    /// Renders the state
    /// @param target
    virtual void render(sf::RenderTarget* target = nullptr) = 0;

    /// Displayes debug window
    /// @param target
    virtual void renderDebug(sf::RenderTarget* target){
        std::stringstream ss;
        sf::Text mousePosText;
        sf::RectangleShape backdrop;
        sf::Font debugFont;

        debugFont.loadFromFile("../../src/Resources/minepixel.ttf");
        ss << "Screen: " << mousePosScreen.x << ", " << mousePosScreen.y << "\n" <<
        "Window: " << mousePosWindow.x << ", " << mousePosWindow.y << "\n" <<
        "View: " << mousePosView.x << ", " << mousePosView.y;
        mousePosText.setFont(font);
        mousePosText.setString(ss.str());
        mousePosText.setPosition(sf::Vector2f(20,20));
        mousePosText.setCharacterSize(15);
        mousePosText.setFillColor(sf::Color::Black);
        backdrop.setSize(sf::Vector2f(300,200));
        backdrop.setFillColor(sf::Color(255,255,255,100));

        target->draw(backdrop);
        target->draw(mousePosText);
    }
};


#endif //SFML_NHZ_STATE_H
