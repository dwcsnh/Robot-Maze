#ifndef CONSOLEFIX_H_INCLUDED
#define CONSOLEFIX_H_INCLUDED

#include <windows.h>
#include"gui/ConsoleColorCode.h"
#include<iostream>

class ConsoleFix{
    public:
        ConsoleFix();
        virtual ~ConsoleFix();
        void displayChar(const int&,const int&,const int &,const COORD& );
        void displayString(const std::string &,const bool&,const COORD&);
        void displayString(const char* ,const bool&,const COORD&);
        void resizeConsole(const int& width,const int& height);
        void gotoXY(const int& ,const int& );
    protected:

    private:
        const int bold_color;/*!< bold color of display string function */
        WORD color_word[27];
        WORD normal_color[27];
};

#endif // CONSOLEFIX_H_INCLUDED
