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

private:
    // Variables
    const int tilesAcross;
    const int tilesDown;

    const int mineCount;

    Minefield minefield;
};
