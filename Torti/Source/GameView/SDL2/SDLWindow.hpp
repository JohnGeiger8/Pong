//
//  SDLWindow.hpp
//  Pong
//
//  Created by John Geiger on 3/20/22.
//
#pragma once

#ifndef SDLWindow_hpp
#define SDLWindow_hpp

#include <string>
#include <SDL2/SDL.h>
#include "IWindow.hpp"

namespace Torti {

class SDLWindow : public IWindow
{
private:
    SDL_Window* m_pWindow;
    std::string mTitle;
    WindowType mWindowType;
    
public:
    SDLWindow();
    virtual ~SDLWindow();
    
    SDL_Window* GetWindow() { return m_pWindow; };
    
    // IWindow implementation
    virtual bool VCreateWindow(std::string title, int xPosition, int yPosition, int width, int height);
    virtual void VShutdown();
    virtual WindowType VGetWindowType();
};

}
#endif /* SDLWindow_hpp */
