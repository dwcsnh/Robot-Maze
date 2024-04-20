#include "logic/MazeLogic.h"
#include<string>

int nonwallExits(IRobot& robot);
int passageExits(IRobot& robot);
int deadend(IRobot& robot);
int corridor(IRobot& robot);
int junction(IRobot& robot);
int crossroad(IRobot& robot);
void control(IRobot& robot);
void exploreControl(IRobot& robot, bool& exploreMode);
void backtrackControl(IRobot& robot, bool& exploreMode);

struct JunctionRecorder
{
    static const int MAX_NUM = 10000;
    int junctionCounter = 0;
    int x[MAX_NUM];
    int y[MAX_NUM];
    std::string heading[MAX_NUM];
    void recordJunction(IRobot& robot)
    {
        x[junctionCounter] = robot.getLocationX();
        y[junctionCounter] = robot.getLocationY();
        switch(robot.getHeading())
        {
            case 1000:
                heading[junctionCounter] = "North"; break;
            case 1001:
                heading[junctionCounter] = "East"; break;
            case 1002:
                heading[junctionCounter] = "South"; break;
            case 1003:
                heading[junctionCounter] = "West";
        }
    }
    bool visited(int a, int b)
    {
        bool check = false;
        if (junctionCounter == 0)
        {
            return false;
        }
        else
        {
            for (int i = 1; i <= junctionCounter; i++)
            {
                if (x[i] == a && y[i] == b)
                {
                    check = true;
                }
            }
        }
        return check;
    }
    int getJunctionIndex(IRobot& robot)
    {
        int junctionIndex;
        for (int i = 1; i <= junctionCounter; i++)
        {
            if (robot.getLocationX() == x[i] && robot.getLocationY() == y[i])
            {
                junctionIndex = i;
            }
        }
        return junctionIndex;

    }
    int getHeading(IRobot& robot)
    {
        int index = getJunctionIndex(robot);
        int intHeading;
        std::string str = heading[index];
        if (str == "North")
        {
            intHeading = IRobot::NORTH;
        }
        else if (str == "South")
        {
            intHeading = IRobot::SOUTH;
        }
        else if (str == "East")
        {
            intHeading = IRobot::EAST;
        }
        else if (str == "West")
        {
            intHeading = IRobot::WEST;
        }
        return intHeading;
    }
    void printJunctionInformation(IRobot& robot)
    {
        int junctionIndex = getJunctionIndex(robot);
        robot.printLog("Junction ");
        robot.printLog(junctionIndex);
        robot.printLog(": ");
        robot.printLog("x = ");
        robot.printLog(x[junctionIndex]);
        robot.printLog(", y = ");
        robot.printLog(y[junctionIndex]);
        robot.printLog(", Heading: ");
        robot.printLog(heading[junctionIndex]);
    }
};
static JunctionRecorder* recorder;

int main()
{
    MazeLogic maze_logic = MazeLogic();
    maze_logic.start(control);

    return 0;
}

void control(IRobot& robot)
{
    static bool exploring = true;
    if (robot.getLocationX() == 1 && robot.getLocationY() == 1)
    {
        recorder = new JunctionRecorder;
    }
    if (exploring == true)
    {
        exploreControl(robot, exploring);
    }
    else
    {
        backtrackControl(robot, exploring);
    }
}

void exploreControl(IRobot& robot, bool& exploreMode)
{
    int direction;
    int exit = nonwallExits(robot);
    if (exit == 1)
    {
        direction = deadend(robot);
        exploreMode = false;
    }
    else if (exit == 2 && robot.look(IRobot::LEFT) == IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
    {
        direction = corridor(robot);
    }
    else if (exit == 2 && (robot.look(IRobot::LEFT) == IRobot::WALL || robot.look(IRobot::RIGHT) == IRobot::WALL))
    {
        if (robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            direction = IRobot::RIGHT;
        }
        else if (robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            direction = IRobot::LEFT;
        }
    }
    else if (exit == 3)
    {
        if (recorder->junctionCounter == 0)
        {
            recorder->junctionCounter++;
            recorder->recordJunction(robot);
            recorder->printJunctionInformation(robot);
        }
        else
        {
            if (recorder->visited(robot.getLocationX(), robot.getLocationY()) == false)
            {
                recorder->junctionCounter++;
                recorder->recordJunction(robot);
                recorder->printJunctionInformation(robot);
            }
        }
        direction = junction(robot);
    }
    else if (exit == 4)
    {
        if (recorder->junctionCounter == 0)
        {
            recorder->junctionCounter++;
            recorder->recordJunction(robot);
            recorder->printJunctionInformation(robot);
        }
        else
        {
            if (recorder->visited(robot.getLocationX(), robot.getLocationY()) == false)
            {
                recorder->junctionCounter++;
                recorder->recordJunction(robot);
                recorder->printJunctionInformation(robot);
            }
        }
        direction = crossroad(robot);
    }
    robot.face(direction);
    robot.advance();
}

void backtrackControl(IRobot& robot, bool& exploreMode)
{
    int exit = nonwallExits(robot);
    int direction;
    if (exit == 2)
    {
        if (robot.look(IRobot::RIGHT) == IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else
        {
            if (robot.look(IRobot::RIGHT) != IRobot::WALL)
            {
                direction = IRobot::RIGHT;
            }
            else if (robot.look(IRobot::LEFT) != IRobot::WALL)
            {
                direction = IRobot::LEFT;
            }
        }
        robot.face(direction);
        robot.advance();
    }
    else if (exit >= 3)
    {
        if (passageExits(robot) > 0)
        {
            exploreMode = true;
            if (recorder->junctionCounter == 0)
            {
                recorder->junctionCounter++;
                recorder->recordJunction(robot);
                recorder->printJunctionInformation(robot);
            }
            else
            {
                if (recorder->visited(robot.getLocationX(), robot.getLocationY()) == false)
                {
                    recorder->junctionCounter++;
                    recorder->recordJunction(robot);
                    recorder->printJunctionInformation(robot);
                }
            }
            direction = junction(robot);
            robot.face(direction);
            robot.advance();
        }
        else
        {
            int heading = recorder->getHeading(robot);
            switch(heading)
            {
                case IRobot::SOUTH:
                    heading = IRobot::NORTH; break;
                case IRobot::NORTH:
                    heading = IRobot::SOUTH; break;
                case IRobot::EAST:
                    heading = IRobot::WEST; break;
                case IRobot::WEST:
                    heading = IRobot::EAST;
            }
            robot.setHeading(heading);
            robot.advance();
        }
    }
}
int nonwallExits(IRobot& robot)
{
    int wall = 0;
    for (int i = IRobot::AHEAD; i <= IRobot::LEFT; i++)
    {
        if (robot.look(i) == IRobot::WALL)
        {
            wall++;
        }
    }
    return 4 - wall;
}

int deadend(IRobot& robot)
{
    int direction;
    for (int i = IRobot::AHEAD; i <= IRobot::LEFT; i++)
    {
        if (robot.look(i) != IRobot::WALL)
        {
            direction = i;
        }
    }
    return direction;
}

int corridor(IRobot& robot)
{
    int direction = IRobot::AHEAD;
    return direction;
}

int junction(IRobot& robot)
{
    int direction = 0;
    for (int i = IRobot::AHEAD; i <= IRobot::LEFT; i++)
    {
        if (robot.look(i) == IRobot::PASSAGE && robot.look(i) != IRobot::BEENBEFORE)
        {
            direction = i;
        }
    }
    if (direction == 0)
    {
        int random_number;
        do
        {
            //Select a random number
            random_number = rand() % 4;

            //Convert this to a direction
            if (random_number == 0)
                direction = IRobot::LEFT;
            else if (random_number == 1)
                direction = IRobot::RIGHT;
            else if (random_number == 2)
                direction = IRobot::BEHIND;
            else
                direction = IRobot::AHEAD;
        } while (robot.look(direction) == IRobot::WALL);
    }
    return direction;
}

int crossroad(IRobot& robot)
{
    int direction = 0;
    for (int i = IRobot::AHEAD; i <= IRobot::LEFT; i++)
    {
        if (robot.look(i) == IRobot::PASSAGE && robot.look(i) != IRobot::BEENBEFORE)
        {
            direction = i;
        }
    }
    if (direction == 0)
    {
        int random_number;
        do
        {
            //Select a random number
            random_number = rand() % 4;

            //Convert this to a direction
            if (random_number == 0)
                direction = IRobot::LEFT;
            else if (random_number == 1)
                direction = IRobot::RIGHT;
            else if (random_number == 2)
                direction = IRobot::BEHIND;
            else
                direction = IRobot::AHEAD;
        } while (robot.look(direction) == IRobot::WALL);
    }
    return direction;
}

int passageExits(IRobot& robot)
{
    int passage = 0;
    for (int i = IRobot::AHEAD; i <= IRobot::LEFT; i++)
    {
        if (robot.look(i) == IRobot::PASSAGE && robot.look(i) != IRobot::BEENBEFORE)
        {
            passage++;
        }
    }
    return passage;
}
