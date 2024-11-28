#ifndef MAZE_H
#define MAZE_H



class Maze {
    class Tile
    {
        int x, y; // Positions
        bool isWall;

        Tile(int x, int y, bool wall);
    };

    Tile maze[][];
    int width, height;

public:
    Maze(); // Constructs a maze of size 1x1
};



#endif //MAZE_H
