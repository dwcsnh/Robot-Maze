#include "logic/MazeLogic.h"

int nonwallExits(IRobot& robot);
int passageExits(IRobot& robot);
int deadend(IRobot& robot);
int corridor(IRobot& robot);
int junction(IRobot& robot);
int crossroad(IRobot& robot);
void control(IRobot& robot);

int main()
{
    MazeLogic maze_logic = MazeLogic();
    maze_logic.start(control);

    return 0;
}

void control(IRobot& robot)
{
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
        direction = junction(robot);
    }
    else if (exit == 4)
    {
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
