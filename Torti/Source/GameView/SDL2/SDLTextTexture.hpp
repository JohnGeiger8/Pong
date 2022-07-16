//
//  SDLTextTexture.hpp
//  Pong
//
//  Created by John Geiger on 7/10/22.
//

#ifndef SDLTextTexture_hpp
#define SDLTextTexture_hpp

#include <SDL2_ttf/SDL_ttf.h>
#include "SDLTexture.hpp"

namespace Torti {

class SDLTextTexture : public SDLTexture
{
    std::string mFontPath;
    TTF_Font* m_pFont;
    std::string mText;
    int mFontSize;
    
public:
    SDLTextTexture();
    SDLTextTexture(std::string text, int fontSize)
        : mText(text), mFontSize(fontSize) { m_pFont = NULL; mFontPath = ""; };
    ~SDLTextTexture();
    
    virtual void VShutdown() override;
    virtual bool VLoadTextureFromFile(std::string path) override;
    
    // 'Change' instead of 'Set' indicates non-trivial set (re-renders texture)
    void ChangeFontSize(int fontSize);
    void ChangeText(std::string text);
    void ChangeFont(std::string path);
    virtual void VSetColor(Uint8 red, Uint8 green, Uint8 blue) override;
};

}
#endif /* SDLTextTexture_hpp */
