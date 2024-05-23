//
// Created by wince on 2024. 05. 05..
//

#include "Board.h"
#include "memtrace.h"

void Board::initBoard() {
    rng.seed(seedVal); //sets random seed

    //Sets board background's parameters
    boardBackground.setSize(sf::Vector2f(gridSize*diff->columns, gridSize*diff->rows));
    boardBackground.setOutlineThickness(3);
    boardBackground.setOutlineColor(sf::Color::Black);

    //Sets the view zoomed and centered on the board
    view->setSize(sf::Vector2f(boardBackground.getSize().x <= boardBackground.getSize().y ?
                              (boardBackground.getSize().y + 55) * (16.f/9.f) : boardBackground.getSize().x + 55,
                              boardBackground.getSize().x <= boardBackground.getSize().y ?
                              boardBackground.getSize().y + 55 : (boardBackground.getSize().x + 55) / (16.f/9.f)));
    view->setCenter(boardBackground.getSize().x/2, (boardBackground.getSize().y-view->getSize().y/11)/2);
}

void Board::setBoard(sf::Vector2i mousePos) {
    int starterX = 0, starterY = 0;
    bool firstCellPlaced = false;

    //Only performs click if the left mouse button is released on the cell
    if (mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < diff->columns && mousePos.y < diff->rows){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            left = true;
        }
    } else if (left != 1){
        left = false;
    }
    if (left == 1 && !sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if (mousePos.x >= 0 && mousePos.y >= 0 && mousePos.x < diff->columns && mousePos.y < diff->rows){
            starterX = mousePos.x;
            starterY = mousePos.y;
            firstCellPlaced = true;
        }
        else{
            left = false;
        }
    }

    //If the first cell is chosen by the user it populates the board with bombs making sure the first cell is a zero
    if (firstCellPlaced){
        //Deletes temporary board
        for (int i = 0; i < diff->columns; ++i) {
            for (int j = 0; j < diff->rows; ++j) {
                delete boardCells[i][j];
                boardCells[i][j] = nullptr;
            }
        }
        //Places the first cell as a ZeroCell
        boardCells[starterX][starterY] = new ZeroCell(cellSprites,starterX,starterY,gridSize,theme);

        //Creates rand engines with the appropriate ranges
        std::uniform_int_distribution<uint32_t> uint_x(0,diff->columns-1);
        std::uniform_int_distribution<uint32_t> uint_y(0,diff->rows-1);

        //Places bombs
        for (int  i = 0;  i < diff->bombs; ++i) {
            bool generating = true;
            while (generating){
                int tmpX = uint_x(rng);
                int tmpY = uint_y(rng);
                if (tmpX < starterX-1 || tmpX > starterX + 1 || tmpY < starterY-1 || tmpY > starterY + 1){
                    if (boardCells[tmpX][tmpY] == nullptr){
                        boardCells[tmpX][tmpY] = new BombCell(cellSprites, tmpX, tmpY, gridSize, theme);
                        generating = false;
                    }
                }
            }
        }

        //Creates the number cells
        for (int i = 0; i < diff->columns; ++i) {
            for (int j = 0; j < diff->rows; ++j) {
                if (boardCells[i][j] == nullptr){
                    int num = checkSurroundings(i, j, BOMB);
                    if (num == 0)
                        boardCells[i][j] = new ZeroCell(cellSprites,i,j,gridSize,theme);
                    else
                        boardCells[i][j] = new NumCell(cellSprites,i,j,gridSize,num,theme);
                }
            }
        }

        //Reveals the first cell
        boardCells[starterX][starterY]->reveal(this);
        started = true;
    }

}

//New
Board::Board(Difficulty* diff, float gridSize, sf::View* view, sf::Texture* cellSprites,std::map<std::string, sf::Color>* theme)
: diff(diff), gridSize(gridSize), view(view), cellSprites(cellSprites), goodFlag(0), badFlag(0), time(0),
gameOverBool(false), started(false), left(false), theme(theme){
    //Allocates the cell matrix
    boardCells = new Cell**[diff->columns];
    for (int i = 0; i < diff->columns; ++i) {
        boardCells[i] = new Cell*[diff->rows];
    }

    //Creates temporary cells until the first cell is chosen
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            boardCells[i][j] = new ZeroCell(cellSprites, i, j, gridSize, theme);
        }
    }

    initBoard();
}

//Load
Board::Board(Difficulty *diff, float gridSize, sf::View *view, sf::Texture *cellSprites, std::map<std::string, sf::Color> *theme, bool load)
: diff(diff), gridSize(gridSize), view(view), cellSprites(cellSprites), goodFlag(0), badFlag(0),
  gameOverBool(false), started(true), left(false), theme(theme), time(0){
    //Loads the game parameters from save file
    std::ifstream ifstream("../../src/Config/save.txt");
    ifstream >> time >> diff->columns >> diff->rows >> diff->bombs;

    //Allocates the boardCell 2d array based on game params
    boardCells = new Cell**[diff->columns];
    for (int i = 0; i < diff->columns; ++i) {
        boardCells[i] = new Cell*[diff->rows];
    }

    //Populates the board from the save file
    int type, revealed, flagged;
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            ifstream >> type >> revealed >> flagged;
            if (type == 0)
                boardCells[i][j] = new ZeroCell(cellSprites,i,j,gridSize,theme);
            else if (type == 10)
                boardCells[i][j] = new BombCell(cellSprites,i,j,gridSize,theme);
            else
                boardCells[i][j] = new NumCell(cellSprites,i,j,gridSize,type,theme);
            boardCells[i][j]->loadCell(revealed, flagged, type);
        }
    }
    ifstream.close();

    initBoard();
}

Board::~Board() {
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            delete boardCells[i][j];
        }
    }
    for (int i = 0; i < diff->columns; ++i) {
        delete[] boardCells[i];
    }
    delete[] boardCells;
}

bool Board::checkWinCondition() {
    //Checks if all flags are correct
    if (badFlag == 0 && goodFlag == diff->bombs){
        bool done = true;
        //Checks if all cells are either revealed or flagged
        for (int i = 0; i < diff->columns && done; ++i) {
            for (int j = 0; j < diff->rows && done; ++j) {
                if(!boardCells[i][j]->getFlagged() && !boardCells[i][j]->getRevealed())
                    done = false;
            }
        }
        return done;
    }
    return false;
}

bool Board::flagged(bool correct) {
    //If there are still flags left
    if (goodFlag + badFlag < diff->bombs){
        //If good flag was placed
        if (correct) goodFlag++;
        //If bad flag was placed
        else badFlag++;
        return true;
    }
    //If there were no remaining flags
    return false;
}

void Board::unflagged(bool correct) {
    //If good flag was removed
    if (correct) goodFlag--;
    //If bad flag was removed
    else badFlag--;
}

int Board::checkSurroundings(int x, int y, int forWhat) {
    int sum = 0;
    //Checks the surrounding 8 cells for given type
    for (int i = x-1; i <= x+1; ++i) {
        for (int j = y-1; j <= y+1; ++j) {
            if (validCoords(i, j)){
                //Special condition for checking flags
                if (forWhat == FLAG && boardCells[i][j]->getFlagged()) sum++;
                //Chacks any other types
                else sum += boardCells[i][j]->isWhat(forWhat);
            }
        }
    }
    return sum;
}

int Board::getRemainigFlagNum() {
    return diff->bombs - goodFlag - badFlag;
}

void Board::revealBombs()
{
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            boardCells[i][j]->revealIfBomb(this);
        }
    }
}

void Board::revealSurroundings(int x, int y) {
    //Calls reveal on the surrounding 8 cells
    for (int i = x-1; i <= x+1; ++i) {
        for (int j = y-1; j <= y+1; ++j) {
            if (validCoords(i, j) && !(i == x && j == y))
                boardCells[i][j]->reveal(this);
        }
    }
}

void Board::updateBoard(sf::Vector2i mousePosGrid) {
    //If board was set it updates the cells
    if (started){
        for (int i = 0; i < diff->columns; ++i) {
            for (int j = 0; j < diff->rows; ++j) {
                boardCells[i][j]->update(mousePosGrid, this);
            }
        }
    }
    //Otherwise it sets the board
    else setBoard(mousePosGrid);
}

void Board::drawBoard(sf::RenderTarget *target) {
    //Calls all of the cells draw function
    target->draw(boardBackground);
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            boardCells[i][j]->drawCell(target);
        }
    }
}

void Board::saveGame() {
    //Saves the game into the save file
    std::ofstream of("../../src/Config/save.txt");
    of << time << " " << diff->columns << " " << diff->rows << " " << diff->bombs << std::endl;
    for (int i = 0; i < diff->columns; ++i) {
        for (int j = 0; j < diff->rows; ++j) {
            boardCells[i][j]->saveCell(&of);
            of<< " " << boardCells[i][j]->getRevealed() << " " << boardCells[i][j]->getFlagged() << std::endl;
        }
    }
    of.close();
}
