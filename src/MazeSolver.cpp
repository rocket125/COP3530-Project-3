#include "MazeSolver.h"

MazeSolver::MazeSolver()
{
    path = vector<pair<unsigned int, unsigned int>>();
    timeElapsed = 0;
}

vector<pair<unsigned int, unsigned int>> MazeSolver::getPath() const
{
    return path;
}

double MazeSolver::getTime() const
{
    return timeElapsed;
}
