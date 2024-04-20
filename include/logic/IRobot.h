#ifndef IROBOT_H_INCLUDED
#define IROBOT_H_INCLUDED

#include "gui/ConsoleColorCode.h"
#include "logic/Maze.h"

#define NORMAL B_GREEN_GRAY
#define HIT_WALL B_GREEN_B_RED
#define FINISH B_GREEN_B_BLUE
#define MONITOR_WIDTH 25

class IRobot
{
public :
    static const int NORTH =1000;
    static const int EAST  =1001;
    static const int SOUTH =1002;
    static const int WEST  =1003;
    static const int AHEAD =2000;
    static const int RIGHT =2001;
    static const int BEHIND =2002;
    static const int LEFT =2003;
    static const int CENTRE=2004;
    static const int WALL =3000;
    static const int PASSAGE =3001;
    static const int BEENBEFORE =4000;
    IRobot();
    virtual ~IRobot();

    COORD        getLocation()      const;
    int          getLocationX()     const;
    int          getLocationY()     const;
    COORD        getPreLocation()   const;
    int          getPreLocationX()  const;
    int          getPreLocationY()  const;
    COORD        getTargetLocation()        const;
    int          getHeading()     const;
    bool         getActive()        const;
    int          getState()         const;
    int          getSteps()         const;
    int          getCollisions()    const;
    int          getRight()         const;
    int          getLeft()          const;
    int          getRunTime()       const;
    int          getBehind()        const;
    int          getAhead()         const;
    int          getPreDirection()  const;
    unsigned int getSleepTime()     const;
    std::string  getControllerName()const;
    bool         getInfoPermission()const;
    std::string  getConsoleInfo() ;


    void         setHeading(const int&);
    void         setMaze(const class Maze&);
    void         setControllerName(const std::string&);
    void         setState(const int& );
    void         setTarget(const COORD&);
    void         setTarget(const int&, const int&);
    void 		 setCollisionSquare(const int&,const int&,const bool&);
	void         clearLog();

    void         face(int) ;
    bool         facingWall() const;
    void         advance();
    int          look(int) const;
    int          handleEvent(const int&);
    void         defaultController();
    void         displayMoveReport();
    void         printLog(std::string);
    void         printLog(int);
    void         printLogEndl(std::string);
    void         printLogEndl(int);

private:
    COORD location;             /*!< Present location of the robot*/
    COORD pre_location;         /*!< previous location of the robot*/
    COORD target;               /*!< the target location */

    int state;                  /*!< hold the color of the robot through section*/

    bool active ;               /*!< the robot start or not*/
    bool **collision_track;     /*!< hold the info of the been before cell or new path*/
    bool getInfo;
    bool change_target;

    unsigned int steps;         /*!< the number of step robot has take*/
    unsigned int collisions;    /*!< the number of collision steps haw made*/
    unsigned int direction;     /*!< Robot geometry direction*/
    unsigned int pre_direction; /*!< Robot previous direction*/
    unsigned int sleep_time ;   /*!< robot sleep time*/
    unsigned int turn_right;    /*!< number of robot turn right*/
    unsigned int turn_left;     /*!< number of time robot turn left*/
    unsigned int run_time;      /*!< number of robot run time*/
    unsigned int turn_behind;   /*!< number of turn backward robot*/
    unsigned int go_ahead;      /*!< number of robot go ahead */


    std::string controller_name; /*!< hold the name of the student controller */
    std::string console_string; /*!< hold the print string of the user passing in */

    class Maze maze;            /*!< robot maze var*/

    bool          checkCollision(const COORD& )const;
    void          start();
    void          restart();

    void          setLocation(const COORD&);
    void          setLocation(const int&, const int&);
    void          setPreLocation(const COORD&);
    void          setPreLocation(const int&, const int&);
    void          setSleepTime(const unsigned int&);

    void          setSteps(const unsigned int &)         ;
    void          setCollisions(const unsigned int &)    ;
    void          setRight(const unsigned int &)         ;
    void          setLeft(const unsigned int &)          ;
    void          setRunTime(const unsigned int &)       ;
    void          setBehind(const unsigned int &)        ;
    void          setAhead(const unsigned int &)         ;
};

#endif // IROBOT_H_INCLUDED
