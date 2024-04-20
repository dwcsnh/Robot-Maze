#ifndef PRIMGENERATOR_H_INCLUDED
#define PRIMGENERATOR_H_INCLUDED

#include"generator/Generator.h"
#include<vector>

class PrimGenerator: public Generator
{
    public :
        PrimGenerator();
        virtual ~PrimGenerator();
        void generateMaze(class Maze&);
    private:
        const int INSIDE;
        const int FRONTER;
        const int OUTSIDE;
        std::vector<COORD> frontier_list;
        void setGridValue(class Maze&, const int& , const int &,const int&);
};

#endif // PRIMGENERATOR_H_INCLUDED
