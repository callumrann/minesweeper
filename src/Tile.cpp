#include "Tile.hpp"

// State changes
void Tile::reveal()
{
    state = State::revealed;
}

void Tile::toggleFlag()
{
    state = State::flagged;
}

// Setters
void Tile::setMine(bool value)
{
    mine = value;
}

void Tile::incrementAdjacentMines()
{
    adjacentMines++;
}

// Getters
bool Tile::isMine() const
{
    return mine;
}

bool Tile::isRevealed() const
{
    return state == State::revealed;
}

bool Tile::isFlagged() const
{
    return state == State::flagged;
}

int Tile::getAdjacentMines() const
{
    return adjacentMines;
}
