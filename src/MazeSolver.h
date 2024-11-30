#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include"Maze.h"

class MazeSolver {
    unsigned int time; // Time it took to solve the maze
    vector<pair<unsigned int, unsigned int>> path; // All the tiles in the path from start to end

public:
    virtual ~MazeSolver() = default;

    MazeSolver();
    virtual void solve(Maze& maze) = 0;
    virtual vector<pair<unsigned int, unsigned int>> getPath() = 0; // Returns a vector containing the path from the start to end
    virtual unsigned int getTime() = 0; // Returns the time taken to solve the maze
};

#endif //MAZESOLVER_H
