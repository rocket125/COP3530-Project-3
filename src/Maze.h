#ifndef MAZE_H
#define MAZE_H
#include <utility>
#include <vector>
#include <string>

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

    // Private functions

public:
    Maze(); // Constructs a maze of 0 size
    // Accessors
    const vector<string>& getMaze();
    pair<int,int> getStartPosition();
    pair<int,int> getEndPosition();
    bool isValidTile(unsigned int x, unsigned int y); // Returns true if the tile is within the maze's bounds
    // Mutators
    void setMaze(const vector<string>& maze); // Replaces maze with a new vector<string> maze
    bool setTile(unsigned int x, unsigned int y, char t); // Replaces a tile within the maze. Returns false if the tile does not exist
    bool setStartPosition(unsigned int x, unsigned int y);
    bool setEndPosition(unsigned int x, unsigned int y);
    // Misc
    void printMaze(); // Prints maze in console

    // Static member functions
    static void loadMazeFromFile(Maze& maze,const string& path);
    static Maze generateMaze(unsigned int width, unsigned int height); // Generates a random maze.
};



#endif //MAZE_H
