#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(int windowSize, float cellSize);
    void drawGameState(sf::RenderWindow &);
    void updateGameState();
    void changeCellState(int x, int y);
    void resetGameState();

private:
    std::vector<std::vector<int>> gameState;
    int windowSize;
    float cellSize;
};
