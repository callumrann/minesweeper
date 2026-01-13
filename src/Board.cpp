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
    minefield(tilesDown, std::vector<Tile>(tilesAcross))
{
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
    if (!inBounds(x, y, tilesAcross, tilesDown))
        return;

    Tile& tile = minefield[y][x];

    if (tile.isRevealed() || tile.isFlagged())
        return;

    tile.reveal();

    if (tile.isMine() || tile.getAdjacentMines() != 0)
        return;

    for (int j = -1; j <= 1; j++)
        for (int k = -1; k <= 1; k++)
        {
            if (j == 0 && k == 0)
                continue;

            revealTiles(x + k, y + j);
        }
}


Minefield& Board::getMinefield()
{
    return minefield;
}

bool Board::clickOnBoard(int mouseX, int mouseY)
{
    return (mouseX >= 0 && mouseX < tilesAcross &&
            mouseY >= 0 && mouseY < tilesDown);

}
