#include "catch/catch_amalgamated.hpp"
#include "../src/Maze.h"

using namespace std;

TEST_CASE("Loading maze 5x5", "[nogui]")
{
    Maze maze;
    Maze::loadMazeFromFile(maze, "mazes/5x5.txt");
    maze.printMaze();
}