#pragma once
#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "CommonFuct.h"

//s?  ki?n chu?t
void handleMouseEvent(SDL_Event event) {

    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN://nh?p chu?t
        std::cout << "Mouse button down at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
    case SDL_MOUSEBUTTONUP:// nh? chu?t
        std::cout << "Mouse button up at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
        break;
    case SDL_MOUSEMOTION:// di chu?t
        std::cout << "Mouse moved to (" << event.motion.x << ", " << event.motion.y << ")" << std::endl;
        break;
    default:
        break;
    }
}



#endif // !MOUSEEVENT_H
