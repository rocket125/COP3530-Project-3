#include "catch/catch_amalgamated.hpp"
#include "../src/Maze.h"

using namespace std;

TEST_CASE("Loading maze 5x5", "[nogui]")
{
    Maze maze;
    Maze::loadMazeFromFile(maze, "mazes/5x5.txt");
    vector<string> actual = maze.getMaze();
    vector<string> expected =
    {"s.###",
"#....",
"..###",
"#...#",
"###.t"};
    maze.printMaze();
    REQUIRE(actual == expected);
}

TEST_CASE("Loading random", "")
{
    srand(123123143);
    Maze maze = Maze::generateMaze(5, 5);
    maze.printMaze();
}