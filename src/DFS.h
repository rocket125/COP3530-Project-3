#ifndef DFS_H
#define DFS_H
#include "MazeSolver.h"
#include<stack>
#include "Maze.h"


class DFS : MazeSolver
{
    set<pair<unsigned int, unsigned int>> visited;

    // Private methods
    stack<pair<unsigned int, unsigned int>> search(stack<pair<unsigned int, unsigned int> > &path, Maze &maze,
                                                   set<pair<unsigned int, unsigned int> > &visited); // Recursive method
    pair<unsigned int, unsigned int> nextPosition(pair<unsigned int, unsigned int> currentTile, Maze& m);
    bool isAdjacentEmpty(pair<unsigned int, unsigned int> currentTile, Maze& m);
    void clear(); // Resets all data
public:
    DFS();
    ~DFS() override;
    void solve(Maze& maze) override; // Solves a maze using Depth-first search algorithm.
    vector<pair<unsigned int, unsigned int>> getPath() const;
    double getTime() const;
};



#endif //DFS_H
