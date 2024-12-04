#include "catch/catch_amalgamated.hpp"
#include "../src/Maze.h"
#include "../src/DFS.h"
#include <iostream>

using namespace std;

TEST_CASE("Loading maze 5x5", "[nogui]")
{
    Maze maze;
    Maze::loadMazeFromFile(maze, "resources/mazes/5x5.txt");
    vector<string> actual = maze.getMaze();
    vector<string> expected =
    {"s.###",
"#....",
"..###",
"#...#",
"###.t"};
    maze.printMaze();
    REQUIRE(actual == expected);
    REQUIRE(maze.getTile(maze.getEndPosition()) == 't');
}

TEST_CASE("Generate random", "[generate]")
{
    srand(123123143);
    Maze maze = Maze::generateMaze(5, 5);
    maze.printMaze();
}

TEST_CASE("2x2 DFS Solve", "[nogui][solve]")
{
    Maze maze;
    Maze::loadMazeFromFile(maze, "resources/mazes/2x2.txt");

    DFS sol = DFS();
    sol.solve(maze);
    vector<pair<unsigned int, unsigned int>> path = sol.getPath();

    /*
    // Prints out path
    for (auto it : path)
    {
        cout << "(" << it.first << ", " << it.second << ")" << endl;
    }
    cout << endl;
    */

    vector<string> actual = maze.getMaze();
    for (auto it : path)
    {
        unsigned int x = it.first, y = it.second;
        string& line = actual[y];
        string newLine = line.substr(0, x) + '+' + line.substr(x + 1, line.length());
        actual[y] = newLine;
    }

    vector<string> expected =
    {"+#",
     "++"};
    REQUIRE(actual == expected);
}

TEST_CASE("5x5 DFS Solve", "[nogui][solve]")
{
    Maze maze;
    Maze::loadMazeFromFile(maze, "resources/mazes/5x5.txt");

    DFS sol = DFS();
    sol.solve(maze);
    vector<pair<unsigned int, unsigned int>> path = sol.getPath();

    /*
    // Prints out path
    for (auto it : path)
    {
        cout << "(" << it.first << ", " << it.second << ")" << endl;
    }
    cout << endl;
    */

    vector<string> actual = maze.getMaze();
    for (auto it : path)
    {
        unsigned int x = it.first, y = it.second;
        string& line = actual[y];
        string newLine = line.substr(0, x) + '+' + line.substr(x + 1, line.length());
        actual[y] = newLine;
    }

    vector<string> expected =
    {"++###",
"#+...",
".+###",
"#+++#",
"###++"};
    REQUIRE(actual == expected);
}

TEST_CASE("401x401 DFS Solve", "[nogui][solve]")
{
    Maze maze;
    Maze::loadMazeFromFile(maze, "resources/mazes/401x401.txt");

    DFS sol = DFS();
    sol.solve(maze);
    vector<pair<unsigned int, unsigned int>> path = sol.getPath();

    vector<string> actual = maze.getMaze();
    for (auto it : path)
    {
        maze.setTile(it, '+');
    }
    maze.printMaze();

    cout << sol.getTime() <<  "ms" << endl;
}