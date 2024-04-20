#ifndef MAZELOGIC_H_INCLUDED
#define MAZELOGIC_H_INCLUDED

#include "logic/Logic.h"
#include "gui/ConsoleSimulation.h"
#include "eventlistener/KeyboardListener.h"
#include <time.h>

class MazeLogic{
    public :
        MazeLogic();
        virtual ~MazeLogic();
        void start(void (*control)(class IRobot& ));
        void start();
    private:
        Logic *logic;
        bool program_exist;
        ConsoleSimulation *console_simulation;
};

#endif // MAZELOGIC_H_INCLUDED
