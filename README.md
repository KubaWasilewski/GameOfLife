# Conway's Game of Life
## Rules of the game

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

Alive cells are white and dead cells are grey.

## Usage
Cells can be made alive or dead by press or drag of left mouse button.

Game can be paused with key press 'P'.

Game can be restarted with key press 'R'.

Game has 3 modes of refresh speed ranging from 1000ms to 50ms and can be selected with key press '1', '2', '3'

## Windows Compilation
Make sure cmake, mingw32 and g++ are installed.

Navigate to build directory
```
cd build
```
Create Makefile
```
cmake -G "MinGW Makefiles" ..
```
Compile
```
mingw32-make
```
Run exe
```
GameOfLife.exe
```
Make sure sfml-graphics-3.dll sfml-system-3.dll sfml-window-3.dll have been moved during build process to build directory if not you can find them in external/SFML-3.0.0/bin

Game of Life explanation with greater detail: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
