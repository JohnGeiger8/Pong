//
//  SDLRenderer.cpp
//  Pong
//
//  Created by John Geiger on 3/20/22.
//

#include "SDLWindow.hpp"
#include "SDLRenderer.hpp"

namespace Torti {

SDLRenderer::SDLRenderer()
    : m_pRenderer(NULL),
      mBackgroundColor(0xFF, 0xFF, 0xFF, 0xFF)
{ }

SDLRenderer::~SDLRenderer()
{
    m_pRenderer = NULL;
}

bool SDLRenderer::VInitRenderer(std::shared_ptr<IWindow> window)
{
    SDLWindow* pWindow = NULL;
    if (window->VGetWindowType() != WindowType::SDL2_Window)
    {
        printf("Error: SDL Renderer can't be initialized with non-SDL window type.");
        return false;
    }
    else
    {
        // Cast window to SDL_Window*
        pWindow = dynamic_cast<SDLWindow*>(window.get());
        if (pWindow == NULL)
        {
            printf("Error: Cast to SDLWindow failed; Renderer can't be initialized.");
            return false;
        }
    }
    
    m_pRenderer = SDL_CreateRenderer(pWindow->GetWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (m_pRenderer == NULL)
    {
        printf( "Error: Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    SDL_SetRenderDrawColor(m_pRenderer, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    return true;
}

///
/// Set the background color for the renderer
/// @Param red color value between 0 and 255
/// @Param green color value between 0 and 255
/// @Param blue color value between 0 and 255
/// @Param alpha opacity value where 0 is transparent and 255 is opaque
///
void SDLRenderer::VSetBackgroundColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    mBackgroundColor = Color(red, green, blue, alpha);
}

///
/// Properly destroy SDL renderer
///
void SDLRenderer::VShutdown()
{
    SDL_DestroyRenderer(m_pRenderer);
    m_pRenderer = NULL;
}

///
/// Clear renderer and set color to prepare for rendering
///
bool SDLRenderer::VPreRender()
{
    SDL_RenderClear(m_pRenderer);
    SDL_SetRenderDrawColor(m_pRenderer, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    return true;
}

///
/// Perform any necessary post-rendering actions
/// FIXME: should SDL_RenderPresent be here?
///
bool SDLRenderer::VPostRender()
{
    SDL_RenderPresent(m_pRenderer);
    return true;
}

///
/// Draw a line with given points and color
/// @Param from point line starts at
/// @Param to point line ends at
/// @Param color color of line
///
void SDLRenderer::VDrawLine(const Point from, const Point to, const Color& color)
{
    SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
    if (SDL_RenderDrawLine(m_pRenderer, from.x, from.y, to.x, to.y) != 0)
        printf("Error: Couldn't draw line. SDL Error: %s\n", SDL_GetError());
    
    // Reset render draw color
    SDL_SetRenderDrawColor(m_pRenderer, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
}


}
