#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include"Maze.h"

class MazeSolver {
protected:
    unsigned int time; // Time it took to solve the maze
    vector<pair<unsigned int, unsigned int>> path; // All the tiles in the path from start to end

public:
    virtual ~MazeSolver() = default;

    MazeSolver();
    virtual void solve(Maze& maze) = 0;
    vector<pair<unsigned int, unsigned int>> getPath() const; // Returns a vector containing the path from the start to end
    unsigned int getTime() const; // Returns the time taken to solve the maze
};

#endif //MAZESOLVER_H
