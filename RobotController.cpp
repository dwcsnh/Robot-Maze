#include "logic/MazeLogic.h"

void controller(IRobot& robot);
int isTargetSouth(IRobot& robot);
int isTargetEast(IRobot& robot);
int southController(IRobot& robot);
int eastController(IRobot& robot);
int westController(IRobot& robot);
int northController(IRobot& robot);
double step = 0;
double directionChange = 0;

int main()
{
    MazeLogic maze_logic = MazeLogic();
    maze_logic.start(controller);

    return 0;
}

/** start of RobotController */
/** Sử dụng đoạn mã: bỏ chú thích đoạn mã
  * Bôi đen đoạn mã -> Chọn Edit -> Chọn Uncomment
  * Sau khi sử dụng: chú thích đoạn mã
  * Bôi đen đoạn mã -> Chọn Edit -> Chọn Comment
  */
//void controller(IRobot& robot)
//{
//    robot.advance(); // move the robot
//}
/** end of RobotController */



/** start of DumbController */
/** Sử dụng đoạn mã: bỏ chú thích đoạn mã
  * Bôi đen đoạn mã -> Chọn Edit -> Chọn Uncomment
  * Sau khi sử dụng: chú thích đoạn mã
  * Bôi đen đoạn mã -> Chọn Edit -> Chọn Comment
  */
//void controller(IRobot& robot)
//{
//    int random_number;
//    int direction;
//
//    if (robot.look(IRobot::AHEAD) == IRobot::WALL || step / directionChange >= 5)
//    {
//        do
//        {
//            // Select a random number
//            random_number = rand() % 4;
//
//            // Convert this to a direction
//            if (random_number == 0)
//                direction = IRobot::LEFT;
//            else if (random_number == 1)
//                direction = IRobot::RIGHT;
//            else if (random_number == 2)
//                direction = IRobot::BEHIND;
//            else
//                direction = IRobot::AHEAD;
//
//        }while(robot.look(direction) == IRobot::WALL);
//
//        robot.face(direction);          // Face the robot in this direction
//        directionChange++;
//        robot.advance();                // and move the robot
//        step++;
//    }
//    else
//    {
//        robot.advance();
//        step++;
//    }
//    int wall = 0;
//    for (int i = IRobot::AHEAD; i <= IRobot::LEFT; i++)
//    {
//        if (robot.look(i) == IRobot::WALL)
//        {
//            wall++;
//        }
//    }
//    if (direction == IRobot::LEFT)
//    {
//        robot.printLog("go left");
//    }
//    else if (direction == IRobot::RIGHT)
//    {
//        robot.printLog("go right");
//    }
//    else if (direction == IRobot::AHEAD)
//    {
//        robot.printLog("go forward");
//    }
//    else
//    {
//        robot.printLog("go backward");
//    }
//    switch (wall)
//    {
//        case 0 : robot.printLog(" @ crossroad"); break;
//        case 1 : robot.printLog(" @ junction"); break;
//        case 2 :
//            if (robot.look(IRobot::RIGHT) == IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
//            {
//                robot.printLog(" @ corridor"); break;
//            }
//            else
//            {
//                robot.printLog(" @ corner"); break;
//            }
//        case 3 : robot.printLog(" @ deadend"); break;
//    }
//    robot.printLog(step / directionChange);
//}
/** end of DumbController */



/** start of BrokenController */
/** Sử dụng đoạn mã: bỏ chú thích đoạn mã
  * Bôi đen đoạn mã -> Chọn Edit -> Chọn Uncomment
  * Sau khi sử dụng: chú thích đoạn mã
  * Bôi đen đoạn mã -> Chọn Edit -> Chọn Comment
  */
void controller(IRobot& robot)
{
    int random_number;
    int direction;

    do
    {
        // Select a random number
        random_number = rand() % 4;

        // Convert this to a direction
        if (random_number == 0)
            direction = IRobot::LEFT;
        else if (random_number == 1)
            direction = IRobot::RIGHT;
        else if (random_number == 2)
            direction = IRobot::BEHIND;
        else
            direction = IRobot::AHEAD;
    } while (robot.look(direction) == IRobot::WALL);

     int south = isTargetSouth(robot);
    int east = isTargetEast(robot);

    robot.printLog("Go to the ");
    if (south == -1 and east == -1)
    {
        robot.printLog("North West.");
    }
    else if (south == -1 and east == 1)
    {
        robot.printLog("North East.");
    }
    else if (south == -1 and east == 0)
    {
        robot.printLog("North.");
    }
    else if (south == 1 and east == -1)
    {
        robot.printLog("South West.");
    }
    else if (south == 1 and east == 1)
    {
        robot.printLog("South East.");
    }
    else if (south == 1 and east == 0)
    {
        robot.printLog("South.");
    }
    else if (south == 0 and east == -1)
    {
        robot.printLog("West.");
    }
    else if (south == 0 and east == 1)
    {
        robot.printLog("East.");
    }
    else if (south == 0 and east == 0)
    {
        robot.printLog("Arrived.");
    }

    if (robot.getHeading() == IRobot::SOUTH)
    {
        direction = southController(robot);
    }
    else if (robot.getHeading() == IRobot::NORTH)
    {
        direction = northController(robot);
    }
    else if (robot.getHeading() == IRobot::EAST)
    {
        direction = eastController(robot);
    }
    else if (robot.getHeading() == IRobot::WEST)
    {
        direction = westController(robot);
    }

    robot.face(direction);          // Face the robot in this direction

    robot.advance();                // and move the robot
}
/** end of BrokenController */

int isTargetSouth(IRobot& robot)
{
    int targetSouth;
    if (robot.getLocationY() < robot.getTargetLocation().Y)
    {
        targetSouth = 1;
    }
    else if (robot.getLocationY() > robot.getTargetLocation().Y)
    {
        targetSouth = -1;
    }
    else if (robot.getLocationY() == robot.getTargetLocation().Y)
    {
        targetSouth = 0;
    }
    return targetSouth;
}

int isTargetEast(IRobot& robot)
{
    int targetEast;
    if (robot.getLocationX() < robot.getTargetLocation().X)
    {
        targetEast = 1;
    }
    else if (robot.getLocationX() > robot.getTargetLocation().X)
    {
        targetEast = -1;
    }
    else if (robot.getLocationX() == robot.getTargetLocation().X)
    {
        targetEast = 0;
    }
    return targetEast;
}

int southController(IRobot& robot)
{
    int direction = IRobot::AHEAD;
    if (isTargetEast(robot) == 1)
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::LEFT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            direction = IRobot::LEFT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            if (robot.look(IRobot::RIGHT) != IRobot::WALL)
            {
                direction = IRobot::RIGHT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    else
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::RIGHT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            direction = IRobot::RIGHT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            if (robot.look(IRobot::LEFT) != IRobot::WALL)
            {
                direction = IRobot::LEFT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    return direction;
}

int northController(IRobot& robot)
{
    int direction = IRobot::AHEAD;
    if (isTargetEast(robot) == 1)
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::RIGHT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            direction = IRobot::RIGHT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            if (robot.look(IRobot::LEFT) != IRobot::WALL)
            {
                direction = IRobot::LEFT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    else
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::LEFT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            direction = IRobot::LEFT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            if (robot.look(IRobot::RIGHT) != IRobot::WALL)
            {
                direction = IRobot::RIGHT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    return direction;
}

int eastController(IRobot& robot)
{
    int direction = IRobot::AHEAD;
    if (isTargetSouth(robot) == 1)
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::RIGHT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            direction = IRobot::RIGHT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            if (robot.look(IRobot::LEFT) != IRobot::WALL)
            {
                direction = IRobot::LEFT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    else
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::LEFT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            direction = IRobot::LEFT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            if (robot.look(IRobot::RIGHT) != IRobot::WALL)
            {
                direction = IRobot::RIGHT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    return direction;
}

int westController(IRobot& robot)
{
    int direction = IRobot::AHEAD;
    if (isTargetSouth(robot) == 1)
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::LEFT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) != IRobot::WALL)
        {
            direction = IRobot::LEFT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::LEFT) == IRobot::WALL)
        {
            if (robot.look(IRobot::RIGHT) != IRobot::WALL)
            {
                direction = IRobot::RIGHT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    else
    {
        if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            int randomNumber;
            randomNumber = rand() % 2;
            if (randomNumber == 0)
            {
                direction = IRobot::AHEAD;
            }
            else
            {
                direction = IRobot::RIGHT;
            }
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) != IRobot::WALL)
        {
            direction = IRobot::RIGHT;
        }
        else if (robot.look(IRobot::AHEAD) != IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            direction = IRobot::AHEAD;
        }
        else if (robot.look(IRobot::AHEAD) == IRobot::WALL && robot.look(IRobot::RIGHT) == IRobot::WALL)
        {
            if (robot.look(IRobot::LEFT) != IRobot::WALL)
            {
                direction = IRobot::LEFT;
            }
            else
            {
                direction = IRobot::BEHIND;
            }
        }
    }
    return direction;
}
