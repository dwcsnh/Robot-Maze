#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include<windows.h>
#include<fstream>
#include<iostream>
#include<malloc.h>

#include "eventlistener/KeyboardListener.h"

class Maze
{
    public :
        Maze();
        Maze(const int& ,const int&);
        Maze(std::string);
        virtual ~Maze();

        static const int MAX     =15;
        static const int WALL    =2;
        static const int PASSAGE =1;

        int getWidth() const;
        int getHeight() const;
        int getGridValue(const int& , const int& )const;
        int getGridValue(const COORD& )const;
        COORD getStart() const;
        COORD getFinish() const;
        int**getGrid() const;

        void setWidth(const int&);
        void setHeight(const int&);
        void setStart(const int & ,const int&);
        void setStart(const COORD &);
        void setFinish(const int & ,const int&);
        void setFinish(const COORD &);
        void setGridValue(const int& , const int&, const int&);
        void setGridValue(const COORD&, const int &);

        Maze& operator= (const class Maze&);


    protected:

    private:
        int** grid;         /*!< var hold the information of maze WALL or PASSAGE*/
        int width;          /*!< contain maze width*/
        int height;         /*!< contain maze height*/
        COORD start_point;  /*!< contain maze start point */
        COORD finish_point; /*!< contain maze finish point*/

        void saveToFile();
};

#endif // MAZE_H_INCLUDED
