#include "inputEventHandler.h"

InputEventHandler::InputEventHandler()
{
    this->quit = false;
}

InputEventHandler::~InputEventHandler()
{
}

/// @brief Polls input events and handles them
void InputEventHandler::Handle()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        this->quit = true;
        break;
    }
}
