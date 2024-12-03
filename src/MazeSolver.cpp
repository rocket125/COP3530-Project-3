#include "MazeSolver.h"

MazeSolver::MazeSolver()
{
    path = vector<pair<unsigned int, unsigned int>>();
    time = 0;
}

vector<pair<unsigned int, unsigned int>> MazeSolver::getPath() const
{
    return path;
}

unsigned int MazeSolver::getTime() const
{
    return time;
}
