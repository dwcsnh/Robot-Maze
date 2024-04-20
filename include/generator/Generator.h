#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include"logic/Maze.h"

class Generator
{
    public :
        Generator();
        virtual~Generator();
        virtual void generateMaze(class Maze&)=0;
    protected:
        static const int NORTH =10;
        static const int EAST = 11;
        static const int SOUTH =12;
        static const int WEST = 13;

        int maze_width;             /*!< maze width*/
        int maze_height;            /*!< maze height*/
        int **generator_grid;       /*!< generator grid*/

        virtual void setGridValue(class Maze&, const int& , const int &,const int&)=0;
};

#endif // GENERATOR_H_INCLUDED
