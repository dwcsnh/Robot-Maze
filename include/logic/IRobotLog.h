#ifndef IROBOTLOG_H_INCLUDED
#define IROBOTLOG_H_INCLUDED

#include "logic/IRobot.h"
#define CONSOLE_WIDTH 25
class IRobotLog
{
    public :
        IRobotLog();
        virtual ~IRobotLog();
        void analysis(class IRobot&);
        void analysisLastRun(const class IRobot&) ;

        std::string getAnalysis() ;
        std::string getLastRunAnalysis() ;
    protected:
    private:
        std::string last_move;
        std::string last_run;
        std::string toString(const int& ) const ;

};

#endif // IROBOTLOG_H_INCLUDED
