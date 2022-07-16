//
//  SDLTexture.cpp
//  Pong
//
//  Created by John Geiger on 7/10/22.
//

#include <SDL2_image/SDL_image.h>
#include "SDLTexture.hpp"
#include "Globals.hpp"

namespace Torti {

///
/// Call VShutdown
///
SDLTexture::~SDLTexture()
{
    VShutdown();
}

///
/// Destroy texture and reset width/height
///
void SDLTexture::VShutdown()
{
    if(m_pTexture != NULL)
    {
        SDL_DestroyTexture(m_pTexture);
        m_pTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

///
/// Load the texture from the given file path
///
bool SDLTexture::VLoadTextureFromFile(std::string path)
{
    // Get rid of preexisting texture
    VShutdown();

    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        SDLRenderer* pRenderer = static_cast<SDLRenderer*>(g_pApp->m_pRenderer.get());
        newTexture = SDL_CreateTextureFromSurface(pRenderer->GetRenderer(), loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    m_pTexture = newTexture;
    return m_pTexture != NULL;
}

///
/// Sets SDL's texture color modulator
///
void SDLTexture::VSetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    mColor = { red, green, blue, 0xFF };
}

///
/// Sets SDL's blending mode
///
void SDLTexture::VSetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(m_pTexture, blending);
}
        
///
/// Set Texture alpha value
///
void SDLTexture::VSetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(m_pTexture, alpha);
}

///
/// Render texture to screen using SDL
///
void SDLTexture::VOnRender()
{
    SDL_Rect renderQuad = { static_cast<int>(mPosition.x), static_cast<int>(mPosition.y), mWidth, mHeight };

    //Set clip rendering dimensions
//    if (clip != NULL )
//    {
//        renderQuad.w = clip->w;
//        renderQuad.h = clip->h;
//    }
    SDLRenderer* pRenderer = static_cast<SDLRenderer*>(g_pApp->m_pRenderer.get());
    SDL_RenderCopy(pRenderer->GetRenderer(), m_pTexture, NULL, &renderQuad);
}


}
