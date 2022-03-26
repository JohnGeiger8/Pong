//
//  SDLRenderer.hpp
//  Pong
//
//  Created by John Geiger on 3/20/22.
//
#pragma once

#ifndef SDLRenderer_hpp
#define SDLRenderer_hpp

#include <SDL2/SDL.h>
#include "IRenderer.hpp"

namespace Torti {

class SDLRenderer : public IRenderer
{
    SDL_Renderer* m_pRenderer;
    Color mBackgroundColor;
    
public:
    SDLRenderer();
    virtual ~SDLRenderer();
    
    // Implement IRenderer interface
    virtual bool VInitRenderer(std::shared_ptr<IWindow> window);
    virtual void VSetBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    virtual void VShutdown();
    virtual bool VPreRender();
    virtual bool VPostRender();
    virtual void VDrawLine(const Point from, const Point to, const Color& color);
};

}

#endif /* SDLRenderer_hpp */
