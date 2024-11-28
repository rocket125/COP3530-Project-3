#include "Maze.h"
#include <iostream>
#include <fstream>

using namespace std;

Maze::Maze()
{
    startPos = make_pair(0,0);
    endPos = make_pair(0,0);
    maze = vector<string>();
}

const vector<string>& Maze::getMaze()
{
    return maze;
}

pair<int, int> Maze::getStartPosition()
{
    return startPos;
}

pair<int, int> Maze::getEndPosition()
{
    return endPos;
}

bool Maze::isValidTile(unsigned int x, unsigned int y)
{
    return (x < maze[y].length() && y < maze.size());
}

void Maze::setMaze(const vector<string>& maze)
{
    this->maze = maze;
}

bool Maze::setTile(unsigned int x, unsigned int y, char t)
{
    if (isValidTile(x, y))
    {
        maze[y][x] = t;
        return true;
    }
    return false;
}

bool Maze::setStartPosition(unsigned int x, unsigned int y)
{
    if (isValidTile(x, y))
    {
        startPos = make_pair(x, y);
        return true;
    }
    return false;
}

bool Maze::setEndPosition(unsigned int x, unsigned int y)
{
    if (isValidTile(x, y))
    {
        endPos = make_pair(x, y);
        return true;
    }
    return false;
}

void Maze::printMaze()
{
    for (unsigned int y = 0; y < maze.size(); ++y)
    {
        for (unsigned int x = 0; x < maze[y].length(); ++x)
        {
            cout << maze[y][x];
        }
        cout << endl;
    }
}

void Maze::loadMazeFromFile(Maze &maze,const string& path)
{
    ifstream file;
    file.open(path);
    if (file.is_open())
    {
        string line;
        vector<string> newMaze;
        while (getline(file, line))
        {
           newMaze.push_back(line);
        }
        maze.setMaze(newMaze);

        file.close();
    }
    else
    {
        cout << "Path is invalid" << endl;
    }
}


