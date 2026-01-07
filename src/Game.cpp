#include "Game.hpp"

#include <iostream>

Game::Game()
    : tileSize {32}, tilesAcross {10}, tilesDown {10}, mineCount {25},
    window(sf::VideoMode({1u*tilesAcross*tileSize,
                1u*tilesDown*tileSize}),"Minesweeper"),
    t("assets/images/minesweeper_tiles.png"),
    s(t)
{
    window.setFramerateLimit(frameRate);
}

void Game::start()
{
    Board board(tilesAcross, tilesDown, mineCount);
    run(board);
}

void Game::run(Board& board)
{
    while (window.isOpen())
    {
        eventLoop(board);
        draw(board);
    }
}

void Game::eventLoop(Board& board)
{   
    Minefield& minefield = board.getMinefield(); 
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        // Key Pressed 
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                window.close();
            }
        }
        // Mouse Pressed 
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Right)
            {
                std::cout << "the right button was pressed" << std::endl;
                int mouseX {mouseButtonPressed->position.x};
                int mouseY {mouseButtonPressed->position.y};

                minefield[mouseY/tileSize][mouseX/tileSize].toggleFlag();
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "the left button was pressed" << std::endl;
                
                int mouseX {mouseButtonPressed->position.x};
                int mouseY {mouseButtonPressed->position.y};

                minefield[mouseY/tileSize][mouseX/tileSize].reveal();
            }
        }
    }
}

void Game::draw(Board& board)
{
    window.clear(sf::Color::White);

    Minefield& minefield = board.getMinefield();
    
    for (int y = 0; y < tilesDown; y++)
    {
        for (int x = 0; x < tilesAcross; x++)
        {
            int spriteLocation;
            if (!minefield[y][x].isRevealed())
            {
                if (minefield[y][x].isFlagged())
                {
                    spriteLocation = flagTile;
                }
                else
                {
                    spriteLocation = emptyTile;
                }
            }
            else if (minefield[y][x].isMine())
            {
                spriteLocation = mineTile;
            }
            else
            {
                spriteLocation = minefield[y][x].getAdjacentMines();
            }

            s.setTextureRect(sf::IntRect(
                        {spriteLocation*tileSize,0},{tileSize,tileSize}));
            s.setPosition({1.f*x*tileSize,1.f*y*tileSize});
            window.draw(s);
        }
    }

    window.display();
}
