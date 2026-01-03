#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>

Game::Game()
        : field(tilesDown, std::vector<int>(tilesAcross, unknownTile)),
        window(sf::VideoMode({tilesAcross*tileSize,
                tilesDown*tileSize}),"Minesweeper"),
        t("assets/images/minesweeper_tiles.png"),
        s(t)
{
    for (auto& row : field)
        for (int& val : row)
            val = unknownTile;
    
    window.setFramerateLimit(60);

    srand(time(0));
}

void Game::run()
{
    while (window.isOpen())
    {
        eventLoop();
        draw();
    }
}

void Game::eventLoop()
{
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

                field[mouseX/tileSize][mouseY/tileSize] = flagTile;
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                std::cout << "the left button was pressed" << std::endl;
                
                int mouseX {mouseButtonPressed->position.x};
                int mouseY {mouseButtonPressed->position.y};

                field[mouseX/tileSize][mouseY/tileSize] = zeroTile;
            }
        }
    }
}

void Game::draw()
{
    window.clear(sf::Color::White);
    
    for (int i = 0; i < tilesAcross; i++)
    {
        for (int j = 0; j < tilesDown; j++)
        {
            s.setTextureRect(sf::IntRect(
                        {field[i][j]*tileSize,0},{tileSize,tileSize}));
            s.setPosition({1.f*i*tileSize,1.f*j*tileSize});
            window.draw(s);
        }
    }

    window.display();
}
