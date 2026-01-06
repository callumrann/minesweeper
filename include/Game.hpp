#pragma once

#include "Board.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
public:
    Game();
    void start();

private:
    // Variables
    enum SpriteLocation
    {
        mineTile = 9, emptyTile, flagTile
    };

    const int tileSize;

    const int tilesAcross;
    const int tilesDown;

    const int mineCount;
    bool firstLeftClick {1};

    sf::RenderWindow window;
    const int frameRate {60};
    
    sf::Texture t;
    sf::Sprite s;

    // Functions
    Board createBoard();
    void run(Board& board);
    void eventLoop(Board& board);
    void draw(Board& board);
};
