#ifndef GENERATORSYSTEM_H
#define GENERATORSYSTEM_H

#include "generator/PrimGenerator.h"
#include "generator/LoopyGenerator.h"
#include "generator/RecursiveGerenator.h"

class GeneratorSystem
{
    public:
        const int PRIM;
        const int LOOPY;
        const int RECURSIVE;
        GeneratorSystem();
        virtual ~GeneratorSystem();

        int getGenerator() const;
        void setGenerator(const unsigned int& );
        void generateMaze(class Maze&);
        int handleEvent(const int&);
    protected:

    private:
        PrimGenerator *prim;
        RecursiveGenerator *recursive;
        LoopyGenerator *loopy;
        unsigned int generator_index;
};

#endif // GENERATORSYSTEM_H
