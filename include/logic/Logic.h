#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "logic/Maze.h"
#include "logic/IRobot.h"
#include "logic/IRobotLog.h"
#include "generator/GeneratorSystem.h"


class Logic
{
    public :
        Logic();
        virtual ~Logic();
        int handleEvent(const int& );
        void controller(void (*control)(class IRobot&));
        void controller();

        Maze getMaze() const;
        IRobot getRobot() const;
        std::string getStepAnalysis() const;
        std::string getRunAnalysis() const;

    protected:
    private:
        const int SIZE_1;            /*!< 10x10 maze size*/
        const int SIZE_2;            /*!< 20x20 maze size*/
        const int SIZE_3;            /*!< 30x30 maze size*/
        bool change_target;
        unsigned int maze_size;      /*!< the default size of the maze */
        Maze* maze;
        IRobot* robot;
        IRobotLog* robot_log;
        GeneratorSystem *generator;
        bool manual;

};

#endif // LOGIC_H_INCLUDED
