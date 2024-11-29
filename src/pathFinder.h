#ifndef PATHSOLVER_H
#define PATHSOLVER_H
#include "Maze.h"

namespace pathFind
{
    vector<pair<unsigned int, unsigned int>> findDFS(Maze maze);
    vector<pair<unsigned int, unsigned int>> findBFS(Maze maze);
}

#endif //PATHSOLVER_H
