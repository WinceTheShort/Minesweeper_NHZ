#include "Game.h"
#include "gtest_lite.h"


int main()
{
#ifndef CPORTA
    Game game; //Creates the game
    game.run(); //Runs the game
    return 0;
#endif

#ifdef CPORTA
    TEST(BOARD, functions)
    {
        Difficulty diff(3,3,0);
        sf::View view;
        sf::Texture cellSprites;
        cellSprites.loadFromFile("../../src/Resources/CellSpriteSheet.png");
        std::map<std::string, sf::Color> theme;
        theme["BtnActive"];
        theme["BtnIdle"];
        theme["BtnHover"];
        theme["Shadow"];

        Board board(&diff, 12, &view, &cellSprites, &theme);
        EXPECT_EQ(0,board.getRemainigFlagNum());
        EXPECT_EQ(0, board.getTime());
        EXPECT_EQ(false, board.getStarted());
        board.setTime(30);
        EXPECT_EQ(30, board.getTime());
        EXPECT_EQ(false, board.validCoords(4,4));
        EXPECT_EQ(true, board.validCoords(1,2));
        EXPECT_EQ(false, board.checkWinCondition());
    }END

    TEST(CELL, functions)
    {
        sf::Texture spriteSheet;
        spriteSheet.loadFromFile("../../src/Resources/CellSpriteSheet.png");
        std::map<std::string, sf::Color> theme;
        theme["BtnActive"];
        theme["BtnIdle"];
        theme["BtnHover"];
        theme["Shadow"];

        ZeroCell zero_cell(&spriteSheet, 2, 2, 12, &theme);
        EXPECT_EQ(ZERO, zero_cell.getType());
        EXPECT_EQ(false, zero_cell.getFlagged());
        EXPECT_EQ(false, zero_cell.getRevealed());

        NumCell num_cell(&spriteSheet, 2, 2, 12, 2, &theme);
        EXPECT_EQ(2, num_cell.getType());
        num_cell.loadCell(true, true, 5);
        EXPECT_EQ(5, num_cell.getType());
        EXPECT_EQ(true, num_cell.getFlagged());
        EXPECT_EQ(true, num_cell.getRevealed());

        BombCell bomb_cell(&spriteSheet, 2, 2, 12, &theme);
        EXPECT_EQ(BOMB, bomb_cell.getType());
        EXPECT_EQ(false, bomb_cell.getFlagged());
        EXPECT_EQ(false, bomb_cell.getRevealed());
    }END

#endif
}