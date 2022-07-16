//
//  SDLTexture.hpp
//  Pong
//
//  Created by John Geiger on 7/10/22.
//

#ifndef SDLTexture_hpp
#define SDLTexture_hpp

#include <SDL2/SDL.h>
#include "Math.hpp"
#include "SDLRenderer.hpp"
#include "ITexture.hpp"

namespace Torti {

class SDLTexture : public ITexture
{
protected:
    SDL_Texture* m_pTexture;
    SDL_Color mColor;
    
    int mWidth;
    int mHeight;
    Point mPosition;
    
public:
    SDLTexture()
        : m_pTexture(NULL),
          mColor({0, 0, 0}),
          mWidth(0),
          mHeight(0),
          mPosition(Point(0, 0))
    { }
    ~SDLTexture();
    
    virtual void VSetColor(Uint8 red, Uint8 green, Uint8 blue);
    virtual void VSetBlendMode(SDL_BlendMode blending);
    virtual void VSetAlpha(Uint8 alpha);
    
    void SetPosition(Point position) { mPosition = position; };
    
    Point GetPosition() { return mPosition; };
    int GetWidth() { return mWidth; };
    int GetHeight() { return mHeight; };
    
    // ITexture implementation
    virtual bool VLoadTextureFromFile(std::string path) override;
    virtual void VOnRender() override;
    virtual void VShutdown() override;
};

}
#endif /* SDLTexture_hpp */
