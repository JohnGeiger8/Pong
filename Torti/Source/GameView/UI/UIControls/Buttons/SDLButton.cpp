//
//  SDLButton.cpp
//  Pong
//
//  Created by John Geiger on 7/10/22.
//

#include "SDLButton.hpp"
#include "Globals.hpp"

namespace Torti {

SDLButton::SDLButton(int width, int height, Point position, SDL_Color color, std::string text, ButtonType button)
    : Button(width, height, Point(0, 0), text, button),
      mColor(color),
      m_pTextTexture(NULL)
{ }

SDLButton::~SDLButton()
{
    
}

///
/// Called for each frame render; draws the button
/// 
void SDLButton::VOnRender(double fTime, float fElapsedTime)
{
    SDLRenderer* pRenderer = static_cast<SDLRenderer*>(g_pApp->m_pRenderer.get());
    SDL_SetRenderDrawColor(pRenderer->GetRenderer(), mColor.r, mColor.g, mColor.b, mColor.a);
    
    // Render button rectangle
    SDL_Rect buttonRect = { static_cast<int>(mPosition.x), static_cast<int>(mPosition.y), mWidth, mHeight };
    
    if (IsFilled())
        SDL_RenderFillRect(pRenderer->GetRenderer(), &buttonRect);
    else
        SDL_RenderDrawRect(pRenderer->GetRenderer(), &buttonRect);
    
    VRenderText();
}

///
/// Called each frame; Update the text color
/// 
void SDLButton::VOnUpdate(int deltaMilliseconds)
{
    // Color of text should be same as rectangle if not filled, otherwise should be black
    IsFilled() ? m_pTextTexture->VSetColor(0x00, 0x00, 0x00) : m_pTextTexture->VSetColor(mColor.r, mColor.g, mColor.b);
}

///
/// Renders the text using the SDLTextTexture member
///
void SDLButton::VRenderText()
{
    int w = m_pTextTexture->GetWidth();
    int h = m_pTextTexture->GetHeight();
    Point position = Point(mPosition.x + mWidth / 2 - w / 2,
                           mPosition.y+ mHeight / 2 - h / 2); // Center text
    m_pTextTexture->SetPosition(position);
    m_pTextTexture->VOnRender();
}

///
/// Loads the button's text using the SDLTextTexture member
///
void SDLButton::LoadButtonText()
{
    m_pTextTexture = std::make_shared<SDLTextTexture>(GetButtonText(), 24);
    
    // Color of text should be same as rectangle if not filled, otherwise should be black
    IsFilled() ? m_pTextTexture->VSetColor(0x00, 0x00, 0x00) : m_pTextTexture->VSetColor(mColor.r, mColor.g, mColor.b);
}

}
