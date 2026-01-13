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
    int flagCount {0};
    bool firstLeftClick {1};

    sf::RenderWindow window;
    const int frameRate {60};
    
    sf::Texture tileTexture;
    sf::Sprite tileSprite;

    sf::Texture statTexture;
    sf::Sprite statSprite;

    sf::Font font;
    sf::Text timerText;
    sf::Text flagText;
    
    sf::Clock gameClock;
    
    // Functions
    Board createBoard();
    void run(Board& board);
    void eventLoop(Board& board);
    void draw(Board& board);
};
