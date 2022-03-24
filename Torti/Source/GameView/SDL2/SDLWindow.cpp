//
//  SDLWindow.cpp
//  Pong
//
//  Created by John Geiger on 3/20/22.
//

#include "SDLWindow.hpp"

namespace Torti {

SDLWindow::SDLWindow()
  : m_pWindow(NULL),
    mTitle(""),
    mWindowType(WindowType::SDL2_Window)
{ }

SDLWindow::~SDLWindow()
{
    m_pWindow = NULL;
}

///
/// Create window with given parameters
///  @Param title window's displayed title
///  @Param xPosition x coordinate of window position
///  @Param yPosition y coordinate of window position
///  @Param width window width
///  @Param height window height
///  @Return true if successful
///
bool SDLWindow::VCreateWindow(std::string title, int xPosition, int yPosition, int width, int height)
{
    if (!SDL_WasInit(SDL_INIT_VIDEO))
    {
        printf("Error: SDL Window can't be initialized without SDL Video initialized.");
        return false;
    }
    
    mTitle = title;
    
    m_pWindow = SDL_CreateWindow(mTitle.c_str(), xPosition, yPosition, width, height, SDL_WINDOW_SHOWN);
    if (m_pWindow == NULL)
    {
        printf("Error: Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

///
/// Destroy window properly. Must be called
///
void SDLWindow::VShutdown()
{
    SDL_DestroyWindow(m_pWindow);
    m_pWindow = NULL;
}

///
/// @Return type of window
/// 
WindowType SDLWindow::VGetWindowType()
{
    return mWindowType;
}

}
