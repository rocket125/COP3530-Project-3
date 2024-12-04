#include "Maze.h"
#include <iostream>
#include <fstream>
#include <random>
#include <set>

using namespace std;

void Maze::markEdges(pair<unsigned int, unsigned int> &tile, set<pair<unsigned int, unsigned int>> &inSet,
    set<pair<unsigned int, unsigned int>> &neighbors, Maze m)
{
    inSet.insert(tile);
    //neighbors.erase(neighbors.find(tile));

    vector<pair<unsigned int, unsigned int>> adj = m.getAdjacentEdges(tile.first, tile.second);
    for (unsigned int i = 0; i < adj.size(); ++i)
    {
        // If this tile is not in inSet and is a wall, then add it to neighbor
        if (inSet.find(adj[i]) == inSet.end())
        {
            neighbors.insert(adj[i]);
        }
    }



}

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

const char Maze::getTile(pair<unsigned int, unsigned int> position) const
{
    return maze[position.second][position.first];
}

vector<pair<unsigned int, unsigned int>> Maze::getAdjacentTiles(pair<unsigned int, unsigned int> position)
{
    unsigned int x = position.first, y = position.second;
    vector<pair<unsigned int, unsigned int>> tiles;
    if (isValidTile(x + 0, y - 1)) // Up
        tiles.push_back(make_pair(x, y - 1));
    if (isValidTile(x + 1, y + 0)) // Right
        tiles.push_back(make_pair(x + 1, y + 0));
    if (isValidTile(x + 0, y + 1)) // Down
        tiles.push_back(make_pair(x + 0, y + 1));
    if (isValidTile(x - 1, y + 0)) // Left
        tiles.push_back(make_pair(x - 1, y + 0));

    return tiles;
}

vector<pair<unsigned int, unsigned int>> Maze::getAdjacentEmptyTiles(pair<unsigned int, unsigned int> position)
{
    vector<pair<unsigned int, unsigned int>> adj = getAdjacentTiles(position);
    vector<pair<unsigned int, unsigned int>> empties;
    // Adds tile to new vector if it does not contain a wall
    for (auto it : adj)
    {
        if (getTile(it) != '#')
        {
            empties.push_back(it);
        }
    }
    return empties;
}

vector<pair<unsigned int, unsigned int>> Maze::getAdjacentGapTiles(unsigned int x, unsigned int y)
{
    vector<pair<unsigned int, unsigned int>> tiles;
    if (isValidTile(x + 0, y - 2)) // Up
        tiles.push_back(make_pair(x, y - 2));
    if (isValidTile(x + 2, y + 0)) // Right
        tiles.push_back(make_pair(x + 2, y + 0));
    if (isValidTile(x + 0, y + 2)) // Down
        tiles.push_back(make_pair(x + 0, y + 2));
    if (isValidTile(x - 2, y + 0)) // Left
        tiles.push_back(make_pair(x - 2, y + 0));

    return tiles;
}

vector<pair<unsigned int, unsigned int>> Maze::getAdjacentGapTiles(pair<unsigned int, unsigned int> position)
{
    return getAdjacentGapTiles(position.first, position.second);
}

vector<pair<unsigned int, unsigned int>> Maze::getAdjacentEdges(unsigned int x, unsigned int y)
{
    vector<pair<unsigned int, unsigned int>> edges;
    if (isValidTile(x + 0, y - 1)) // Up
        edges.push_back(make_pair(x, y - 1));
    if (isValidTile(x + 1, y + 0)) // Right
    edges.push_back(make_pair(x + 1, y + 0));
    if (isValidTile(x + 0, y + 1)) // Down
        edges.push_back(make_pair(x + 0, y + 1));
    if (isValidTile(x - 1, y + 0)) // Left
        edges.push_back(make_pair(x - 1, y + 0));

    return edges;
}

vector<pair<unsigned int, unsigned int>> Maze::getTilesFromEdge(unsigned int x,
    unsigned int y)
{
    pair<unsigned int, unsigned int> t1, t2;
    // Find if this edge is connecting tiles horizontally or vertically
    if (y % 2 == 1) // Vertical
    {
        t1 = make_pair(x, y - 1);
        t2 = make_pair(x, y + 1);
    }
    else           // Horizontal
    {
        t1 = make_pair(x + 1, y);
        t2 = make_pair(x - 1, y);
    }
    vector<pair<unsigned int, unsigned int>> tiles;
    tiles.push_back(t1);
    tiles.push_back(t2);

    return tiles;
}

vector<pair<unsigned int, unsigned int>> Maze::getTilesFromEdge(
    pair<unsigned int, unsigned int> edge)
{
    return getTilesFromEdge(edge.first, edge.second);
}

pair<unsigned int,unsigned int> Maze::getStartPosition()
{
    return startPos;
}

pair<unsigned int,unsigned int> Maze::getEndPosition()
{
    return endPos;
}

bool Maze::isValidTile(int x, int y)
{
    bool flag = x >= 0 && x < maze[y].length();
    flag = flag && y >= 0 && y < maze.size();
    return flag;
}

bool Maze::isValidTile(pair<int, int> tile)
{
    return isValidTile(tile.first, tile.second);
}

void Maze::setMaze(const vector<string>& maze)
{
    this->maze = maze;
}

bool Maze::setTile(unsigned int x, unsigned int y, char t)
{
    if (isValidTile(x, y))
    {
        string& line = maze[y];
        string newLine = line.substr(0, x) + t + line.substr(x + 1, line.length());
        maze[y] = newLine;
        return true;
    }
    return false;
}

bool Maze::setTile(pair<unsigned int, unsigned int>& position, char t)
{
    unsigned int x = position.first;
    unsigned int y = position.second;
    return setTile(x, y, t);
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

        maze.setStartPosition(0 , 0);
        maze.setEndPosition(newMaze[0].length() - 1, newMaze.size() - 1);

        file.close();
    }
    else
    {
        cout << "Path is invalid" << endl;
    }
}

Maze Maze::generateMaze(unsigned int width, unsigned int height)
{
    vector<string> maze;

    // Creates an empty grid with an empty space at every even index
    for (int x = 0; x < height; ++x)
    {
        string line;
        for (int y = 0; y < width; ++y)
        {
            if (x % 2 == 0 && y % 2 == 0)
            {
                line.append(".");
            }
            else
            {
                line.append("#");
            }
        }
        maze.push_back(line);
    }

    Maze m;
    m.setMaze(maze);

    // Prim's Algorithm for maze generation
    set<pair<unsigned int, unsigned int>> in, neighborEdges;
    // Start at a random empty tile
    pair<unsigned int, unsigned int> rTile = make_pair(rand() % (width / 2) * 2, rand() % (height / 2) * 2);
    markEdges(rTile, in, neighborEdges, m);

    while (!neighborEdges.empty())
    {
        // Pick a random neighboring edge
        auto it = neighborEdges.begin();
        advance(it, rand() % neighborEdges.size());
        pair<unsigned int, unsigned int> edge = *it;


        vector<pair<unsigned int, unsigned int>> connectedTiles = m.getTilesFromEdge(edge);
        // If either tiles is not from the edge, add its edges to neighborEdges and set it to an empty space
        if (in.find(connectedTiles[0]) == in.end())
        {
            markEdges(connectedTiles[0], in, neighborEdges, m);
            m.setTile(edge, '.');
        }
        else if (in.find(connectedTiles[1]) == in.end())
        {
            markEdges(connectedTiles[1], in, neighborEdges, m);
            m.setTile(edge, '.');
        }
        neighborEdges.erase(edge);
    }

    // Setting start and end of the maze
    // Start is always at the top left and end is always at the bottom right

    m.setStartPosition(0,0);
    m.setTile(0, 0, 's');
    m.setEndPosition(m.getMaze()[0].length() - 1, m.getMaze().size() - 1);
    m.setTile(m.getMaze()[0].length() - 1, m.getMaze().size() - 1, 't');

    return m;
}


