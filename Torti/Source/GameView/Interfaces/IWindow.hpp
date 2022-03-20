//
//  IWindow.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef IWindow_hpp
#define IWindow_hpp

#include <string>

namespace Torti {

enum class WindowType
{
    SDL2_Window
};

///
/// Defines a window containing the application
///
class IWindow
{
public:
    virtual bool VCreateWindow(std::string title, int xPosition, int yPosition, int width, int height) = 0;
    virtual void VShutdown() = 0;
    virtual WindowType VGetWindowType() = 0;
};

}
#endif /* IWindow_hpp */
