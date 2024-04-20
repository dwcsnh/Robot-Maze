#include "logic/MazeLogic.h"
#include<string>

int nonwallExits(IRobot& robot);
int passageExits(IRobot& robot);
int deadend(IRobot& robot);
int corridor(IRobot& robot);
int junction(IRobot& robot);
int crossroad(IRobot& robot);
void control(IRobot& robot);

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
    void printJunctionInformation(IRobot& robot)
    {
        int junctionIndex;
        for (int i = 1; i <= junctionCounter; i++)
        {
            if (robot.getLocationX() == x[i] && robot.getLocationY() == y[i])
            {
                junctionIndex = i;
            }
        }
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

int main()
{
    MazeLogic maze_logic = MazeLogic();
    maze_logic.start(control);

    return 0;
}

void control(IRobot& robot)
{
    static JunctionRecorder* recorder;
    if (robot.getLocationX() == 1 && robot.getLocationY() == 1)
    {
        recorder = new JunctionRecorder;
    }
    int direction;
    int exit = nonwallExits(robot);
    if (exit == 1)
    {
        direction = deadend(robot);
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
        if (recorder->visited(robot.getLocationX(), robot.getLocationY()) == false)
        {
            recorder->junctionCounter++;
            recorder->recordJunction(robot);
            recorder->printJunctionInformation(robot);
        }
        direction = junction(robot);
    }
    else if (exit == 4)
    {
        if (recorder->visited(robot.getLocationX(), robot.getLocationY()) == false)
        {
            recorder->junctionCounter++;
            recorder->recordJunction(robot);
            recorder->printJunctionInformation(robot);
        }
        direction = crossroad(robot);
    }
    robot.face(direction);
    robot.advance();
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
