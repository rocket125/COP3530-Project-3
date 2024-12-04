#ifndef MAZE_H
#define MAZE_H
#include <utility>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Maze {
    /*
     * '.' is an empty space
     * '#' is a wall
     * 's' is the start
     * 't' is the end
     */

    vector<string> maze;
    pair<int,int> startPos, endPos;

    // Private methods

    // Private static methods
    static void markEdges(pair<unsigned int, unsigned int>& tile, set<pair<unsigned int, unsigned int>>& inSet, set<pair<unsigned int, unsigned int>>& neighbors, Maze m); // Removes tile from neighbor set and places it in inSet. Its neighbors is placed in the neighbors set.

public:
    Maze(); // Constructs a maze of 0 size
    // Accessors
    const vector<string>& getMaze();
    vector<pair<unsigned int, unsigned int>> getAdjacentTiles(unsigned int x, unsigned int y);
    vector<pair<unsigned int, unsigned int>> getAdjacentTiles(pair<unsigned int, unsigned int> tile);
    vector<pair<unsigned int, unsigned int>> getAdjacentEdges(unsigned int x, unsigned int y);
    vector<pair<unsigned int, unsigned int>> getTilesFromEdge(unsigned int x, unsigned int y);
    vector<pair<unsigned int, unsigned int>> getTilesFromEdge(pair<unsigned int, unsigned int> edge);
    pair<int,int> getStartPosition();
    pair<int,int> getEndPosition();
    bool isValidTile(int x, int y); // Returns true if the tile is within the maze's bounds
    bool isValidTile(pair<int, int> tile); // Returns true if the tile is within the maze's bounds
    // Mutators
    void setMaze(const vector<string>& maze); // Replaces maze with a new vector<string> maze
    bool setTile(unsigned int x, unsigned int y, char t); // Replaces a tile within the maze. Returns false if the tile does not exist
    bool setTile(pair<unsigned int, unsigned int>& position, char t); // Replaces a tile within the maze. Returns false if the tile does not exist
    bool setStartPosition(unsigned int x, unsigned int y);
    bool setEndPosition(unsigned int x, unsigned int y);
    // Misc
    void printMaze(); // Prints maze in console

    // Static member functions
    static void loadMazeFromFile(Maze& maze,const string& path);
    static Maze generateMaze(unsigned int width, unsigned int height); // Generates a random maze.
};

#endif //MAZE_H
