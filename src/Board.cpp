#include "Board.hpp"

Board::Board(int tilesAcross, int tilesDown, int mineCount)
    : tilesAcross {tilesAcross},
    tilesDown {tilesDown},
    mineCount {mineCount},
    minefield(tilesDown, std::vector<Tile>(tilesDown))
{
    for (int y = 0; y < tilesDown; y++)
    {
        for (int x = 0; x < tilesAcross; x++)
        {
            minefield[y][x] = Tile{};
        }
    }

    placeMines(mineCount);
}

void Board::placeMines(int mineCount)
{
   return; 
}

Minefield& Board::getMinefield()
{
    return minefield;
}
