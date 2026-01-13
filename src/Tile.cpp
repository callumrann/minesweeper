#include "Tile.hpp"

// State changes
void Tile::reveal()
{
    state = State::revealed;
}

int Tile::toggleFlag()
{
    if (state == State::flagged)
    {
        state = State::hidden;
        return -1;
    }

    else if (state == State::hidden)
    {
        state = State::flagged;
        return 1;
    }
    return 0;
}

// Modifying values
void Tile::placeMine()
{
    mine = 1;
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
