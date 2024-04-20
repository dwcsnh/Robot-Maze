#ifndef RECURSIVEGERENATOR_H_INCLUDED
#define RECURSIVEGERENATOR_H_INCLUDED

#include "generator/Generator.h"
#include <stack>


class RecursiveGenerator : public Generator{
    public:
        RecursiveGenerator();
        virtual ~RecursiveGenerator();
        void generateMaze(class Maze&);
    private:
        /*!\ structure of generator grid type*/
        struct Cell{
            bool top_wall;
            bool bottom_wall;
            bool left_wall;
            bool right_wall;
            bool visited;
            int display_num;

            /*!\ default structure constructor
            */
            Cell()
            {
                top_wall = true;
                bottom_wall = true;
                left_wall = true;
                right_wall = true;
                visited = false;
                display_num =Maze::WALL;
            }
        };


        std::stack<COORD> back_track_coord;

        void setGridValue(class Maze&, const int&,const int &, const int&);

};

#endif // RECURSIVEGERENATOR_H_INCLUDED
