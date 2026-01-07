#include "Board.hpp"

#include <random>
#include <algorithm>

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
    std::vector<std::pair<int,int>> positions;
    for (int y = 0; y < tilesDown; y++)
        for (int x = 0; x < tilesAcross; x++)
            positions.emplace_back(x,y);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for (int i = 0; i < mineCount; i++)
    {
        int x = positions[i].first;
        int y = positions[i].second;
        minefield[y][x].setMine(true);
        
        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                if ((j == 0 && k == 0) || y+j < 0 || y+j >= tilesDown ||
                        x+k < 0 || x+k >= tilesAcross)
                    continue;

                minefield[y+j][x+k].incrementAdjacentMines();
            }
        }
    }
}

Minefield& Board::getMinefield()
{
    return minefield;
}
