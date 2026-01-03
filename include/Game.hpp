#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
public:
    Game();
    void run();

private:
    // Variables
    const int tileSize {32};

    const int tilesAcross {10};
    const int tilesDown {10};

    const int mineCount {25};
    bool firstLeftClick {1};

    enum TileCode 
    {
        zeroTile, oneTile, twoTile, threeTile, fourTile, fiveTile,
        sixTile, sevenTile, eightTile, mineTile, unknownTile, flagTile,
    };

    std::vector<std::vector<int>> field;

    sf::RenderWindow window;
    
    sf::Texture t;
    sf::Sprite s;

    // Functions
    void eventLoop();
    void draw();
};
