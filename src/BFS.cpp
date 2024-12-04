#include "BFS.h"
#include "MazeSolver.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <unordered_map>

using namespace std;

pair<unsigned int, unsigned int> BFS::nextPosition(pair<unsigned int, unsigned int> currentTile, Maze &m)
{
    vector<pair<unsigned int, unsigned int>> adj = m.getAdjacentEmptyTiles(currentTile);
    for (unsigned int i = 0; i < adj.size(); i++)
    {
        if (visited.find(adj[i]) == visited.end())
            return adj[i];
    }

    return make_pair(0,0);
}

bool BFS::isAdjacentEmpty(pair<unsigned int, unsigned int> currentTile, Maze& m)
{
    // Returns true if there is at least one adjacent tile unvisited
    vector<pair<unsigned int, unsigned int>> adj = m.getAdjacentEmptyTiles(currentTile);
    for (unsigned int i = 0; i < adj.size(); i++)
    {
        if (visited.find(adj[i]) == visited.end())
            return true;
    }

    return false;
}

void BFS::clear()
{
    timeElapsed = 0;
    path.clear();
    visited.clear();
}

BFS::BFS()
{
    timeElapsed = 0;
    path = vector<pair<unsigned int, unsigned int>>();
    visited = set<pair<unsigned int, unsigned int>>();
}

BFS::~BFS()
= default;

void BFS::solve(Maze &maze)
{
    auto t = chrono::high_resolution_clock::now();
    clear();

    // Use a queue instead of stack for BFS
    queue<pair<unsigned int, unsigned int>> q;
    // Use an unordered_map to track parent tiles for path reconstruction
    unordered_map<pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>, pair_hash> parent;

    pair<unsigned int, unsigned int> start = maze.getStartPosition();
    pair<unsigned int, unsigned int> end = maze.getEndPosition();

    q.push(start);
    visited.insert(start);

    // BFS traversal
    while (!q.empty())
    {
        pair<unsigned int, unsigned int> current = q.front();
        q.pop();

        // Check if reached end
        if (current == end)
            break;

        // Explore adjacent tiles
        vector<pair<unsigned int, unsigned int>> adj = maze.getAdjacentEmptyTiles(current);
        for (const auto& nextTile : adj)
        {
            if (visited.find(nextTile) == visited.end())
            {
                q.push(nextTile);
                visited.insert(nextTile);
                parent[nextTile] = current;
            }
        }
    }

    // Reconstruct path from end to start
    pair<unsigned int, unsigned int> current = end;
    while (current != start)
    {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back(start);

    // Reverse path to go from start to end
    reverse(path.begin(), path.end());

    chrono::duration<double> elapsed = chrono::high_resolution_clock::now() - t;
    timeElapsed = elapsed.count();
}

vector<pair<unsigned int, unsigned int>> BFS::getPath() const
{
    return path;
}

double DFS::getTime() const
{
    return timeElapsed;
}