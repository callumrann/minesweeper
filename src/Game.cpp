#include "Game.hpp"

#include <iostream>
#include <format>
#include <string>

Game::Game()
    : tileSize {32}, tilesAcross {10}, tilesDown {10}, mineCount {25},
    window(sf::VideoMode({1u*tilesAcross*tileSize,
                1u*(tilesDown+2)*tileSize}),"Minesweeper"),
    tileTexture("assets/images/minesweeper_tiles.png"),
    tileSprite(tileTexture),
    statTexture("assets/images/stat_background.png"),
    statSprite(statTexture),
    font("assets/fonts/DS-DIGI.TTF"),
    timerText(font),
    flagText(font)
{
    timerText.setString("000");
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    
    auto timerTextWidth = timerText.getLocalBounds().size;
    timerText.setPosition({2.f*tileSize - timerTextWidth.x*0.5f,
            (tilesDown+0.5f)*tileSize});
    
    flagText.setString(std::to_string(mineCount));
    flagText.setCharacterSize(24);
    flagText.setFillColor(sf::Color::Black);

    auto flagTextWidth = flagText.getLocalBounds().size;
    flagText.setPosition({1.f*(tilesAcross-2)*tileSize - flagTextWidth.x*0.5f,
            (tilesDown+0.5f)*tileSize});
    
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
                int mouseX {mouseButtonPressed->position.x};
                int mouseY {mouseButtonPressed->position.y};

                if (!board.clickOnBoard(mouseX/tileSize, mouseY/tileSize))
                    continue;

                flagCount += minefield[mouseY/tileSize][mouseX/tileSize].toggleFlag();
            }
            else if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                int mouseX {mouseButtonPressed->position.x};
                int mouseY {mouseButtonPressed->position.y};
                
                if (!board.clickOnBoard(mouseX/tileSize, mouseY/tileSize))
                    continue;

                if (firstLeftClick)
                {
                    firstLeftClick = 0;
                    board.placeMines(mineCount, mouseX/tileSize,mouseY/tileSize);
                    gameClock.reset();
                    gameClock.start();
                }
                
                board.revealTiles(mouseX/tileSize, mouseY/tileSize);
            }
        }
    }
}

void Game::draw(Board& board)
{
    window.clear(sf::Color(155,175,185));
    
    // Draw board
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

            tileSprite.setTextureRect(sf::IntRect(
                        {spriteLocation*tileSize,0},{tileSize,tileSize}));
            tileSprite.setPosition({1.f*x*tileSize,1.f*y*tileSize});
            window.draw(tileSprite);
        }
    }

    // Draw bottom tab
    statSprite.setPosition({1.f*tileSize,(tilesDown+0.5f)*tileSize});
    window.draw(statSprite);

    if (!firstLeftClick && gameClock.getElapsedTime().asSeconds() < 1000)
    timerText.setString(std::format("{:03}", 
                static_cast<int>(gameClock.getElapsedTime().asSeconds())));
    window.draw(timerText);


    statSprite.setPosition({1.f*(tilesAcross-3)*tileSize,(tilesDown+0.5f)*tileSize});
    window.draw(statSprite);
    
    flagText.setString(std::to_string(mineCount - flagCount));
    window.draw(flagText);

    window.display();
}
