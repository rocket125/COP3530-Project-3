#ifndef BFS_H
#define BFS_H
#include "MazeSolver.h"
#include <queue>
#include "Maze.h"

// This implements breadth-first search to solve the maze.
class BFS : MazeSolver
{
    set<pair<unsigned int, unsigned int>> visited;

    pair<unsigned int, unsigned int> nextPosition(pair<unsigned int, unsigned int> currentTile, Maze& m);
    bool isAdjacentEmpty(pair<unsigned int, unsigned int> currentTile, Maze& m);
    void clear();
public:
    BFS();
    ~BFS() override;
    void solve(Maze& maze) override;
    vector<pair<unsigned int, unsigned int>> getPath() const;
};

#endif //BFS_H
