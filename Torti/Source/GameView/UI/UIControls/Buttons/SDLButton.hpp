//
//  SDLButton.hpp
//  Pong
//
//  Created by John Geiger on 7/10/22.
//
#pragma once

#ifndef SDLButton_hpp
#define SDLButton_hpp

#include <SDL2/SDL.h>
#include "Button.hpp"
#include "SDLTextTexture.hpp"

namespace Torti {

///
/// Button that uses SDL for rendering
///
class SDLButton : public Button
{
    SDL_Color mColor;
    std::shared_ptr<SDLTextTexture> m_pTextTexture;

public:
    SDLButton(int width, int height, Point position, SDL_Color color, std::string text = "", ButtonType button = OK_BTN);
    virtual ~SDLButton();
    
    void SetButtonColor(SDL_Color color) { mColor = color; };
    SDL_Color GetColor() { return mColor; };

    // IControl implementation
    virtual void VOnRender(double fTime, float fElapsedTime) override;
    virtual void VOnRestore() override { };
    virtual void VOnLostDevice() override { };
    virtual void VOnUpdate(int deltaMilliseconds) override;
    virtual bool VOnAppMessage(AppMessage msg) override { return false; };
    
private:
    void LoadButtonText();
    void VRenderText();
};

}
#endif /* SDLButton_hpp */
