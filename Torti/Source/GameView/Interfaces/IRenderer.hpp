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
#include "Color.hpp"
#include "IWindow.hpp"

namespace Torti {

enum class RendererType
{
    SDL2_Renderer
};

///
/// Defines a general renderer
///
class IRenderer
{
public:
    virtual bool VInitRenderer(std::shared_ptr<IWindow> window)=0;
    virtual void VSetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)=0;
    virtual void VShutdown()=0;
    virtual bool VPreRender()=0;
    virtual bool VPostRender()=0;
    virtual void VDrawLine(const Point from, const Point to, const Color& color)=0;
};

}

#endif /* IRenderer_hpp */
