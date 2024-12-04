#ifndef MAZE_H
#define MAZE_H
#include <utility>
#include <vector>
#include <string>
#include <set>

using namespace std;

// This struct is used in BFS solving
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

class Maze {
    /*
     * '.' is an empty space
     * '#' is a wall
     * 's' is the start
     * 't' is the end
     */

    vector<string> maze;
    pair<unsigned int,unsigned int> startPos, endPos;

    // Private methods
    // Maze generation methods
    vector<pair<unsigned int, unsigned int>> getAdjacentGapTiles(unsigned int x, unsigned int y); // Returns tiles 2 tiles away in cardinal directions from position
    vector<pair<unsigned int, unsigned int>> getAdjacentGapTiles(pair<unsigned int, unsigned int> position); // Returns tiles 2 tiles away in cardinal directions from position
    vector<pair<unsigned int, unsigned int>> getAdjacentEdges(unsigned int x, unsigned int y); // Returns the connected edges of the current position
    vector<pair<unsigned int, unsigned int>> getTilesFromEdge(unsigned int x, unsigned int y); // Returns a vector of two tiles touching this edge.
    vector<pair<unsigned int, unsigned int>> getTilesFromEdge(pair<unsigned int, unsigned int> edge); // Returns a vector of two tiles touching this edge.
    // Private static methods
    static void markEdges(pair<unsigned int, unsigned int>& tile, set<pair<unsigned int, unsigned int>>& inSet, set<pair<unsigned int, unsigned int>>& neighbors, Maze m); // Removes tile from neighbor set and places it in inSet. Its neighbors is placed in the neighbors set.

public:
    Maze(); // Constructs a maze of 0 size
    // Accessors
    const vector<string>& getMaze(); // Returns a vector<string> reference of the Maze. O(1)
    const char getTile(pair<unsigned int, unsigned int> position) const; // Returns the char of the tile in this position. O(1)
    vector<pair<unsigned int, unsigned int>> getAdjacentTiles(pair<unsigned int, unsigned int> position); // Returns the adjacent tiles from position. O(1): only checks the surrounding tiles
    vector<pair<unsigned int, unsigned int>> getAdjacentEmptyTiles(pair<unsigned int, unsigned int> position); // Return adjacent empty tiles from position O(1): calls getAdjacentTiles()
    pair<unsigned int, unsigned int> getStartPosition(); // O(1)
    pair<unsigned int, unsigned int> getEndPosition(); // O(1)
    bool isValidTile(int x, int y); // Returns true if the tile is within the maze's bounds. O(1)
    bool isValidTile(pair<int, int> tile); // Returns true if the tile is within the maze's bounds. O(1)
    // Mutators
    void setMaze(const vector<string>& maze); // Replaces maze with a new vector<string> maze. O(n) where n is total tiles in the new maze
    bool setTile(unsigned int x, unsigned int y, char t); // Replaces a tile within the maze. Returns false if the tile does not exist. O(n) where n is all the tiles in the row with the targeted tile
    bool setTile(pair<unsigned int, unsigned int>& position, char t); // Replaces a tile within the maze. Returns false if the tile does not exist. O(n): calls setTile(unsigned int x, unsigned int y, char t)
    bool setStartPosition(unsigned int x, unsigned int y); // O(1)
    bool setEndPosition(unsigned int x, unsigned int y); // O(1)
    // Misc
    void printMaze(); // Prints maze in console. O(n) where n is all the tiles in the maze.

    // Static member functions
    static void loadMazeFromFile(Maze& maze,const string& path); // O(n) where n is all the tiles in the maze
    static Maze generateMaze(unsigned int width, unsigned int height); // Generates a random maze using Prim's algorithm
};

#endif //MAZE_H
