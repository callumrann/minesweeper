#include "Board.hpp"

#include <random>
#include <algorithm>

namespace
{
    bool isWithinOne(int x, int y, int cx, int cy)
    {
        return std::abs(x - cx) <= 1 && std::abs(y - cy) <= 1;
    }

    bool inBounds(int x, int y, int width, int height)
    {
        return (x >= 0 && x < width) && (y >= 0 && y < height);
    }
}

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
}

void Board::placeMines(int mineCount, int xClick, int yClick)
{
    std::vector<std::pair<int,int>> positions;
    for (int y = 0; y < tilesDown; y++)
        for (int x = 0; x < tilesAcross; x++)
        {
            if (!isWithinOne(xClick,yClick,x, y))
                positions.emplace_back(x,y);
        }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for (int i = 0; i < mineCount; i++)
    {
        int x = positions[i].first;
        int y = positions[i].second;
        minefield[y][x].placeMine();
        
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
            {
                if ((j == 0 && k == 0) || 
                        !inBounds(x+k,y+j,tilesAcross,tilesDown))
                    continue;

                minefield[y+j][x+k].incrementAdjacentMines();
            }
    }
}

void Board::revealTiles(int x, int y)
{
    if (minefield[y][x].isFlagged())
        return;

    if (minefield[y][x].getAdjacentMines() != 0)
    {
        minefield[y][x].reveal();
        return;
    }

    for (int j = -1; j <= 1; j++)
        for (int k = -1; k <= 1; k++)
        {
            if (!inBounds(x+k,y+j,tilesAcross,tilesDown))
                continue;
            
            if (!minefield[y+j][x+k].isRevealed())
            {
                minefield[y+j][x+k].reveal();

                if (minefield[y+j][x+k].getAdjacentMines() == 0)
                {
                    revealTiles(x+k,y+j);
                }
            }
        }
}

Minefield& Board::getMinefield()
{
    return minefield;
}
