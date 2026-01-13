#pragma once

#include "Tile.hpp"

#include <vector>

using Minefield = std::vector<std::vector<Tile>>;

class Board
{
public:
    Board(int tilesAcross, int tilesDown, int mineCount);
    
    void placeMines(int count, int xClick, int yClick);
    void revealTiles(int x, int y);

    Minefield& getMinefield();

    bool clickOnBoard(int mouseX, int mouseY);

private:
    // Variables
    const int tilesAcross;
    const int tilesDown;

    const int mineCount;

    Minefield minefield;
};
