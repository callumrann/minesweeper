#include "Tile.hpp"

#include <vector>

using Minefield = std::vector<std::vector<Tile>>;

class Board
{
public:
    Board(int tilesAcross, int tilesDown, int mineCount);
    
    Minefield& getMinefield();

private:
    // Variables
    const int tilesAcross;
    const int tilesDown;

    const int mineCount;

    Minefield minefield;

    // Functions
    void placeMines(int count);
};
