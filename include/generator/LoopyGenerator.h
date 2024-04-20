#ifndef LOOPYGENERATOR_H_INCLUDED
#define LOOPYGENERATOR_H_INCLUDED

#include"generator/Generator.h"
#include"generator/PrimGenerator.h"
#define RATE 3

class LoopyGenerator : public Generator{
    public:
        LoopyGenerator();
        virtual ~LoopyGenerator();
        void generateMaze(class Maze&);
    private:
        void setGridValue(class Maze& , const int&,const int&,const int&);
};


#endif // LOOPYGENERATOR_H_INCLUDED
