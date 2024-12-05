#include "DFS.h"
#include "MazeSolver.h"
#include <iostream>
#include <chrono>

using namespace std;

pair<unsigned int, unsigned int> DFS::nextPosition(pair<unsigned int, unsigned int> currentTile, Maze &m)
{
    vector<pair<unsigned int, unsigned int>> adj = m.getAdjacentEmptyTiles(currentTile);
    for (unsigned int i = 0; i < adj.size(); ++i)
    {
        if (visited.find(adj[i]) == visited.end())
            return adj[i];
    }

    // Should never get to this point
    return make_pair(0,0);
}

bool DFS::isAdjacentEmpty(pair<unsigned int, unsigned int> currentTile, Maze& m)
{
    // Returns true if there is at least one adjacent tile unvisited
    vector<pair<unsigned int, unsigned int>> adj = m.getAdjacentEmptyTiles(currentTile);
    for (unsigned int i = 0; i < adj.size(); ++i)
    {
        if (visited.find(adj[i]) == visited.end())
            return true;
    }

    return false;
}

void DFS::clear()
{
    timeElapsed = 0;
    path.clear();
    visited.clear();
}

DFS::DFS()
{
    timeElapsed = 0;
    path = vector<pair<unsigned int, unsigned int>>();
    visited = set<pair<unsigned int, unsigned int>>();
}

DFS::~DFS()
= default;

void DFS::solve(Maze &maze)
{
    auto t = chrono::high_resolution_clock::now();
    clear();

    stack<pair<unsigned int, unsigned int>> p;
    p.emplace(maze.getStartPosition());
    visited.emplace(maze.getStartPosition());

    // Continue until reaches the end
    while (p.top() != maze.getEndPosition())
    {
        // Checks if the surrounding tiles are empty
        if (isAdjacentEmpty(p.top(), maze))
        {
            pair<unsigned int, unsigned int> nextTile = nextPosition(p.top(), maze);
            visited.emplace(nextTile);
            p.push(nextTile);
        }
        else
        {
            // Tile is dead end, pop from stack
            p.pop();
        }
    }

    // Copies every tile in p to path
    while (!p.empty())
    {
        path.push_back(p.top());
        p.pop();
    }

    chrono::duration<double, std::milli> elapsed = chrono::high_resolution_clock::now() - t;
    timeElapsed = elapsed.count();
}

vector<pair<unsigned int, unsigned int>> DFS::getPath() const
{
    return path;
}

double DFS::getTime() const
{
    return timeElapsed;
}
