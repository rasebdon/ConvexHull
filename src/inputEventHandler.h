#pragma once
#include <SDL.h>
#include <map>

class InputEventHandler
{
    public:
        bool quit;
        std::map<int, bool> keyboard;
        InputEventHandler();
        ~InputEventHandler();

        void Handle();
};