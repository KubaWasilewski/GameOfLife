#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

void printProgramRules()
{
    std::cout << "Welcome to Conway's Game of Life" << '\n';
    std::cout << "Alive cells are white and dead cells are grey" << '\n';
    std::cout << "You can pause and unpause the game by pressing 'p'" << '\n';
    std::cout << "You can press left mouse button to change the state of the cells if game is paused" << '\n';
    std::cout << "You can press 'r' to reset the grid" << '\n';
    std::cout << "You can select the speed of the game by pressing '1', '2' or '3'" << '\n';
    std::cout << "Here are the 4 rules of the game" << '\n';
    std::cout << "1. Any live cell with fewer than two live neighbours dies, as if by underpopulation" << '\n';
    std::cout << "2. Any live cell with two or three live neighbours lives on to the next generation" << '\n';
    std::cout << "3. Any live cell with more than three live neighbours dies, as if by overpopulation" << '\n';
    std::cout << "4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction" << '\n';
}

int main()
{
    // window and cell are squares, make sure window size is divided by cell size evenly
    const unsigned int windowSize{1200};
    const int cellSize{25};
    sf::RenderWindow window(sf::VideoMode({windowSize, windowSize}), "Game Of Life", sf::Style::Close);
    window.setFramerateLimit(60);
    Game game(windowSize, cellSize);
    bool mouseDrag = false;
    bool gamePaused = true;
    sf::Vector2i mousePos{};
    sf::Vector2i previousCell{};
    printProgramRules();
    int delay = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // main program loop
    while (window.isOpen())
    {
        // window events loop
        while (const std::optional event = window.pollEvent())
        {
            // close window event
            if (event->is<sf::Event::Closed>())
                window.close();
            // change cell state and start dragging mouse if left mouse button clicked
            else if (gamePaused && event->is<sf::Event::MouseButtonPressed>() && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
            {
                mouseDrag = true;
                mousePos = sf::Mouse::getPosition(window);
                game.changeCellState(mousePos.x / cellSize, mousePos.y / cellSize);
                previousCell = mousePos / cellSize;
            }
            // stop dragging mouse if left mouse button released
            else if (event->is<sf::Event::MouseButtonReleased>() && event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left)
            {
                mouseDrag = false;
            }
            // handle key pressed events
            else if (event->is<sf::Event::KeyPressed>())
            {
                // pause and unpause game if 'P' pressed
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::P)
                {
                    mouseDrag = false;
                    switch (gamePaused)
                    {
                    case false:
                        gamePaused = true;
                        break;
                    case true:
                        gamePaused = false;
                        break;
                    }
                }
                // reset game state if 'R' pressed
                else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::R)
                {
                    game.resetGameState();
                }
                // change speed of the game with '1', '2', '3'
                else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Num1)
                {
                    delay = 1000;
                }
                else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Num2)
                {
                    delay = 400;
                }
                else if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Num3)
                {
                    delay = 100;
                }
            }
        }

        // continue changing cell states if mouse dragging
        if (mouseDrag && gamePaused)
        {
            mousePos = sf::Mouse::getPosition(window);
            if (previousCell != mousePos / cellSize)
            {
                game.changeCellState(mousePos.x / cellSize, mousePos.y / cellSize);
                previousCell = mousePos / cellSize;
            }
        }

        // only update game state if enough time passed
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        if (!gamePaused && duration.count() >= delay)
        {
            start = std::chrono::high_resolution_clock::now();
            game.updateGameState();
        }

        // update display
        window.clear(sf::Color::Black);
        game.drawGameState(window);
        window.display();
    }
    return 0;
}
