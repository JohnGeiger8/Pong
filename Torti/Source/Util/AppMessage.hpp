//
//  AppMessage.hpp
//  Pong
//
//  Created by John Geiger on 7/9/22.
//
#pragma once

#ifndef AppMessage_hpp
#define AppMessage_hpp

#include <SDL2/SDL.h>

namespace Torti {

using SDL_EventPtr = std::shared_ptr<SDL_Event>;

enum MessageType
{
    SDL
};

struct AppMessage
{
    SDL_EventPtr pEvent;
};

}
#endif /* AppMessage_hpp */
