//
// Created by wince on 2024. 04. 22.
//

#include "GameState.h"

void GameState::initFonts() {
    this->font.loadFromFile("../../src/Resources/minepixel.ttf");
    int* tmp = new int[10];
}

void GameState::initKeybinds() {
    std::ifstream file("../../src/Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key_name;
        std::string key;
        while (file >> key_name >> key)
            this->keybinds[key_name] = this->supportedKeys->at(key);
    }
    file.close();
}

void GameState::initButtons() { //Creates the buttons
    this->buttons["QUIT"] = new Button(30,30,60,60,0,5,theme,nullptr,"",0,0, &buttonSprites,1);
    this->buttons["RETRY"] = new Button(110,30,60,60,0,5,theme,nullptr,"",0,0, &buttonSprites,0);
    this->buttons["SAVE"] = new Button(190,30,60,60,0,5,theme,nullptr,"",0,0, &buttonSprites,2);
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*>* states,
                     Difficulty *difficulty, std::map<std::string, sf::Color>* theme, bool load)
: State(window, supportedKeys, states), iButton(), isShiftPressed(false), gridSize(12), currentDifficulty (difficulty),
correctFlag(0), wrongFlag(0), gameEnded(false), win(false), clock(0), theme(theme){
    //Init functions
    initFonts();
    initKeybinds();
    initButtons();

    //Sets views default parameters and view speed
    view.setSize(window->getSize().x, window->getSize().y);
    view.setCenter(window->getSize().x / 2, window->getSize().y / 2);
    viewSpeed = 200;

    //Loads sprites from files
    buttonSprites.loadFromFile("../../src/Resources/ButtonSprites.png");
    cellSprites.loadFromFile("../../src/Resources/CellSpriteSheet.png");

    //Sets the background color's parameters
    backgroundColor.setFillColor(theme->at("BtnActive"));
    backgroundColor.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

    //Sets the background border's parameters
    backgroundBorder.setSize(sf::Vector2f(backgroundColor.getSize().x - 40, backgroundColor.getSize().y - 40));
    backgroundBorder.setPosition(20, 20);
    backgroundBorder.setOutlineColor(sf::Color::Black);
    backgroundBorder.setOutlineThickness(20);
    backgroundBorder.setFillColor(sf::Color(0, 0, 0, 0));

    //Sets the UI background's parameters
    uiBackground.setFillColor(theme->at("BtnIdle"));
    uiBackground.setSize(sf::Vector2f(window->getSize().x - 40, 80));
    uiBackground.setPosition(20,20);
    uiBackground.setOutlineThickness(20);
    uiBackground.setOutlineColor(sf::Color::Black);

    //Sets bomb counter's parameters
    bombCounterText.setFont(font);
    bombCounterText.setFillColor(sf::Color::Black);
    bombCounterText.setCharacterSize(60);
    bombCounterText.setPosition(300, 30);
    bombCounterText.setLetterSpacing(0.2);

    //Sets bomb icon's parameters
    bombCounterIcon.setSize(sf::Vector2f(60, 60));
    bombCounterIcon.setTexture(&cellSprites);
    bombCounterIcon.setTextureRect(sf::IntRect(10*12,0,12,12));
    bombCounterIcon.setFillColor(theme->at("BtnIdle"));

    //Sets you win text's parameters
    youWinText.setFont(font);
    youWinText.setFillColor(sf::Color::Black);
    youWinText.setCharacterSize(60);
    youWinText.setString("You Win");
    youWinText.setPosition(window->getSize().x/2 - youWinText.getGlobalBounds().width/2, 30);

    //Sets game over text's parameters
    gameOverText.setFont(font);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setCharacterSize(60);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(window->getSize().x/2 - youWinText.getGlobalBounds().width/2, 30);

    //Sets clock text's parameters
    clockText.setFont(font);
    clockText.setFillColor(sf::Color::Black);
    clockText.setCharacterSize(60);
    clockText.setPosition(1600, 30);

    //Creates a new board
    if (!load)
        board = new Board(currentDifficulty, gridSize, &view, &cellSprites, theme);
    else
        board = new Board(currentDifficulty, gridSize, &view, &cellSprites, theme, true);

    //The board gives back the starting time (used for loading saved game's time)
    clock = board->getTime();
}

GameState::~GameState() {
    deleteButtons();
    delete board;
}

void GameState::endState() {

}

void GameState::checkEndGameCondition() {
    if (board->checkWinCondition()){ //If all bombs are flagged and cells are revealed
        win = true;
        gameEnded = true;
    } else if (board->gameOver())//If a bomb is clicked
    {
        gameEnded = true;
        board->revealBombs();
    }
}

void GameState::handleInput(const float &dt) {
    //Checks quit
    checkForQuit();

    //Checks end game condition
    checkEndGameCondition();

    //Shift for faster view movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !isShiftPressed){
        viewSpeed *= 2;
        isShiftPressed = true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && isShiftPressed){
        viewSpeed /= 2;
        isShiftPressed = false;
    }

    //View left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        view.move(-viewSpeed * dt,0.f);
    //View right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        view.move(viewSpeed * dt,0.f);
    //View up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        view.move(0.f,-viewSpeed * dt);
    //View down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        view.move(0.f,viewSpeed * dt);

    //Zoom in
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && view.getSize().x > 200){
        view.setSize(view.getSize().x/1.01,view.getSize().y/1.01);
        viewSpeed /= 1.005;
    }
    //Zoom out
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && view.getSize().x < window->getSize().x){
        view.setSize(view.getSize().x*1.01,view.getSize().y*1.01);
        viewSpeed *= 1.005;
    }
}

void GameState::handleButtons() { //Updates and handles buttons
    //Quit
    if (this->buttons["QUIT"]->isPressed())
        this->quit = true;

    //Retry
    if (this->buttons["RETRY"]->isPressed()){
        gameEnded = false;
        win = false;
        clock = 0;
        timerClock.restart();
        delete board;
        board = new Board(currentDifficulty, gridSize, &view, &cellSprites, theme);
    }

    //Save
    if (this->buttons["SAVE"]->isPressed() && !gameEnded){
        board->setTime((int)timerClock.getElapsedTime().asSeconds() + clock);
        board->saveGame();
    }
}

void GameState::updateMousePositions() {
    //Screen
    this->mousePosScreen = sf::Mouse::getPosition();

    //Window
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    //View
    this->mousePosView = this->window->mapPixelToCoords(mousePosWindow, view);

    //Grid
    mousePosGrid = sf::Vector2i(mousePosView.x/gridSize,mousePosView.y/gridSize);
}

void GameState::updateBombCounter() {
    std::stringstream ss;
    ss << board->getRemainigFlagNum();
    bombCounterText.setString(ss.str());
    bombCounterIcon.setPosition(bombCounterText.getPosition().x + bombCounterText.getGlobalBounds().width + 15, 30);
}

void GameState::updateClock() {
    if (!board->getStarted())
        timerClock.restart();
    if (clock >= 99*60)
        clock = 0;
    int time;
    time = (int)timerClock.getElapsedTime().asSeconds() + clock;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::fixed << std::setprecision(0);
    ss << time/60 << std::setw(1) << ":" << std::setw(2) << time%60;
    clockText.setString(ss.str());
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtons();
    this->handleInput(dt);
    updateBombCounter();
    if (!gameEnded)
        updateClock();

    //Disables board interaction if mouse is not in board, is over ui elements or the game is over
    if (mousePosWindow.y > 120 && board->boardBackground.getGlobalBounds().contains(mousePosView) && !gameEnded)
        board->updateBoard(mousePosGrid);
}

void GameState::render(sf::RenderTarget *target = nullptr) {
    if (!target)
        target= this->window;

    target->draw(backgroundColor); //background color

    //Set view
    window->setView(view);

    //Game Elements
    board->drawBoard(target); //draws board

    //Reset view
    window->setView(window->getDefaultView());

    //Gui
    target->draw(backgroundBorder); //border
    target->draw(uiBackground); //ui background
    this->renderButtons(target); //buttons
    if (gameEnded){
        if (win){target->draw(youWinText);}
        else{target->draw(gameOverText);}
    }
    target->draw(bombCounterText);
    target->draw(bombCounterIcon);
    target->draw(clockText);

    //Debug
    //renderDebug(target);
}

