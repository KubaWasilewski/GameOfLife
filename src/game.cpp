#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <typeinfo>

// Game Of Life rules.
// 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
// 2. Any live cell with two or three live neighbours lives on to the next generation.
// 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
// 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
// alive = 1 dead = 0

// check if coordinates are within gameState space
bool inBounds(int x, int y, int size)
{
    return x >= 0 && x <= size - 1 && y >= 0 && y <= size - 1;
}

// return count of alive cells, check 8 cells around the cell by itterating changeX and changeY arrays
int countNeighbours(int x, int y, std::vector<std::vector<int>> gameState)
{
    int count{0};
    int changeInX[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int changeInY[] = {1, 1, 1, 0, -1, -1, -1, 0};
    int neighbourX = {x};
    int neighbourY = {y};
    for (int i = 0; i < 8; i++)
    {
        neighbourX = x + changeInX[i];
        neighbourY = y + changeInY[i];
        if (inBounds(neighbourX, neighbourY, gameState.size()) && gameState[neighbourX][neighbourY] == 1)
            count++;
    }
    return count;
}

Game::Game(int windowSize, float cellSize)
{
    Game::gameState = std::vector<std::vector<int>>(windowSize / cellSize, std::vector<int>(windowSize / cellSize, 0));
    Game::windowSize = windowSize;
    Game::cellSize = cellSize;
}

void Game::resetGameState()
{
    Game::gameState = std::vector<std::vector<int>>(Game::windowSize / Game::cellSize, std::vector<int>(Game::windowSize / Game::cellSize, 0));
}

// draw a grid of dead and alive cells
void Game::drawGameState(sf::RenderWindow &window)
{
    const sf::Color ALIVECOLOR = sf::Color(210, 210, 210);
    const sf::Color DEADCOLOR = sf::Color(66, 66, 66);
    sf::RectangleShape deadRectangle = sf::RectangleShape({Game::cellSize, Game::cellSize});
    deadRectangle.setFillColor(DEADCOLOR);
    deadRectangle.setOutlineColor(sf::Color(0, 0, 0));
    deadRectangle.setOutlineThickness(2.f);
    sf::RectangleShape aliveRect = sf::RectangleShape({Game::cellSize, Game::cellSize});
    aliveRect.setFillColor(ALIVECOLOR);
    aliveRect.setOutlineColor(sf::Color(0, 0, 0));
    aliveRect.setOutlineThickness(2.f);
    for (int i = 0; i < Game::windowSize / Game::cellSize; i++)
    {
        for (int j = 0; j < Game::windowSize / Game::cellSize; j++)
        {
            deadRectangle.setPosition({i * Game::cellSize, j * Game::cellSize});
            if (Game::gameState[i][j] == 1)
            {
                aliveRect.setPosition({i * Game::cellSize, j * Game::cellSize});
                window.draw(aliveRect);
            }
            else
            {
                deadRectangle.setPosition({i * Game::cellSize, j * Game::cellSize});
                window.draw(deadRectangle);
            }
        }
    }
}

// switch state of the cell from dead to alive or alive to dead
void Game::changeCellState(int x, int y)
{
    switch (Game::gameState[x][y])
    {
    case 0:
        Game::gameState[x][y] = 1;
        break;
    case 1:
        Game::gameState[x][y] = 0;
        break;
    }
}

// update gameState according to game rules
void Game::updateGameState()
{
    int neigbourCount{};

    std::vector<std::vector<int>> newGameState(Game::windowSize / Game::cellSize, std::vector<int>(Game::windowSize / Game::cellSize, 0));
    for (int i = 0; i < Game::windowSize / Game::cellSize; i++)
    {
        for (int j = 0; j < Game::windowSize / Game::cellSize; j++)
        {
            neigbourCount = countNeighbours(i, j, Game::gameState);
            if (Game::gameState[i][j])
            {
                newGameState[i][j] = neigbourCount == 2 || neigbourCount == 3;
            }
            else
            {
                newGameState[i][j] = neigbourCount == 3;
            }
        }
    }
    Game::gameState = newGameState;
}
