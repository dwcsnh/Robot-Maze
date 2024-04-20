#ifndef KEYBOARDLISTENER_H_INCLUDED
#define KEYBOARDLISTENER_H_INCLUDED

#include<windows.h>

class KeyboardListener
{
    public :
        static int getUserInteract();
    private:
        static const int BUTTON_DELAY = 500;
};

#endif // KEYBOARDLISTENER_H_INCLUDED
