#ifndef CONSOLESIMULATION_H_INCLUDED
#define CONSOLESIMULATION_H_INCLUDED

#include "gui/ConsoleFix.h"
#include "logic/Maze.h"
#include"logic/IRobot.h"
#include"logic/IRobotLog.h"
#include <deque>

class ConsoleSimulation
{
    public:
        ConsoleSimulation();
        virtual~ConsoleSimulation();
        void drawMaze(const class Maze&);
        void drawRobot(const class IRobot&);
        void drawBorder();
        void drawGuide();
        int handleEvent(const class Maze& , const class IRobot&,const int &);
        void addMonitor(const std::string&);
        void addConsole(const std::string&);
        void displayMonitor() const;
        void displayConsole() const;
    private:
        void  clearMonitor();
        void  clearConsole();
        void  newMaze(const class IRobot&, const class Maze&);
        void  reDrawTarget(const class Maze&);

        const int JUMP_STEP;
        const int BLOCK ;
        const int ARROW_RIGHT;
        const int ARROW_LEFT;
        const int ARROW_UP;
        const int ARROW_DOWN;
        const int ROBOT_STUN_TIME;

        const int MONITOR_HEIGHT;
        const int CONSOLE_HEIGHT;
        const int DISPLAY_WIDTH;
        const int BUTTON_DELAY;


        COORD board_start_point;
        COORD maze_start_point;
        COORD last_finish;
        class ConsoleFix *console_fix;

        int maze_width;
        int maze_height;
        int maze_size;
        int gen_num;
        int sleep_time_pos ;
        int monitor_index;
        int console_index;

        bool robot_start;
        bool change_target;

        std::deque<std::string> monitor_deque;
        std::deque<std::string> console_deque;

        std::string controller_name;

        void clearMaze();
};

#endif // CONSOLESIMULATION_H_INCLUDED
