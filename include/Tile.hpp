#pragma once

class Tile
{
public:
    enum class State
    {
        hidden, revealed, flagged,
    };

    Tile() = default;

    // State changes
    void reveal();
    int toggleFlag();

    // Modifying balues
    void placeMine();
    void incrementAdjacentMines();

    // Getters
    bool isMine() const;
    bool isRevealed() const;
    bool isFlagged() const;
    int getAdjacentMines() const;

private:
    bool mine {false};
    State state {State::hidden};
    int adjacentMines {0};
};
