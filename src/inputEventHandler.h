#pragma once
#include <SDL.h>

class InputEventHandler
{
    public:
        bool quit;
        InputEventHandler();
        ~InputEventHandler();

        void Handle();
};