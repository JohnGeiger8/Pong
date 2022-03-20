//
//  IRenderer.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef IRenderer_hpp
#define IRenderer_hpp

#include <memory>
#include "Math.hpp"
#include "IWindow.hpp"

namespace Torti {

enum class RendererType
{
    SDL2_Renderer
};

class Color;

///
/// Defines a general renderer
///
class IRenderer
{
public:
    virtual bool InitRenderer(std::shared_ptr<IWindow> window)=0;
    virtual void VSetBackgroundColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)=0;
    virtual void VShutdown()=0;
    virtual bool VPreRender()=0;
    virtual bool VPostRender()=0;
    virtual void VDrawLine(const Point from, const Point to, const Color& color)=0;
};

}

#endif /* IRenderer_hpp */
