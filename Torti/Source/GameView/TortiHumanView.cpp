//
//  TortiHumanView.cpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//

#include "TortiHumanView.hpp"
#include "Globals.hpp"
#include "SDLMixerAudioSystem.hpp"
#include "SortBySharedPtrContent.hpp"

namespace Torti {

const unsigned int SCREEN_REFRESH_RATE = (1000/60); // 60 frames per second

TortiHumanView::TortiHumanView()
{
    InitAudio();
}

TortiHumanView::~TortiHumanView()
{
    while (!mScreenElements.empty())
    {
        mScreenElements.pop_front();
    }
}

///
/// Creates view-specific elements from an XML file that defines all the elements in the game
///
bool TortiHumanView::LoadGame(XmlElementPtr pLevelData)
{
    return VLoadGameDelegate(pLevelData);
}

void TortiHumanView::VOnRender(double fTime, float fElapsedTime)
{
    mCurrentTick = 0;
    
    // Drawing already occurred this frame, so return
    if (mCurrentTick == mLastRender)
        return;
    
    // Check if we should draw
    if (mRunFullSpeed || ((mCurrentTick - mLastRender) > SCREEN_REFRESH_RATE))
    {
        // Render the scene
        if (g_pApp->m_pRenderer->VPreRender())
        {
            mScreenElements.sort(SortBy_SharedPtr_Content<IScreenElement>());
            
            for (std::shared_ptr<IScreenElement> element : mScreenElements)
            {
                if (element->VIsVisible())
                {
                    element->VOnRender(fTime, fElapsedTime);
                }
            }
            
            mLastRender = mCurrentTick;
        }
        g_pApp->m_pRenderer->VPostRender();
    }
}

void TortiHumanView::VOnRestore()
{
    for (const ScreenElementPtr &element : mScreenElements)
    {
        element->VOnRestore();
    }
}

void TortiHumanView::VOnLostDevice()
{
    for (const ScreenElementPtr &element : mScreenElements)
    {
        element->VOnLostDevice();
    }
}

void TortiHumanView::VPushElement(ScreenElementPtr pElement)
{
    mScreenElements.push_front(pElement);
}

void TortiHumanView::VRemoveElement(ScreenElementPtr pElement)
{
    mScreenElements.remove(pElement);
}

void TortiHumanView::TogglePause(bool active)
{
    // FIXME: implement if needed?
}

bool TortiHumanView::InitAudio()
{
    if (!g_pAudio)
    {
        g_pAudio = std::shared_ptr<AudioSystem>(new SDLMixerAudioSystem());
    }
    
    if (!g_pAudio)
        return false;
    
    if (!g_pAudio->VInitialize())
        return false;
    
    return true;
}

void TortiHumanView::VOnUpdate(unsigned long deltaMs)
{
    for (const ScreenElementPtr &element : mScreenElements)
    {
        element->VOnUpdate(deltaMs);
    }
}

bool TortiHumanView::VOnAppMessage(AppMessage msg)
{
    // Iterate through screen elements in reverse order since top one should process first
    for (ScreenElementList::reverse_iterator it = mScreenElements.rbegin(); it != mScreenElements.rend(); it++)
    {
        if ((*it)->VIsVisible())
        {
            if ((*it)->VOnAppMessage(msg))
                return true;
        }
    }
    
    bool result = false;
    switch (msg.pEvent->type)
    {
        case SDL_KEYDOWN:
            if (mKeyboardHandler)
            {
                result = mKeyboardHandler->VOnKeyDown(msg.pEvent->key.keysym.sym);
            }
            break;
            
        case SDL_KEYUP:
            if (mKeyboardHandler)
            {
                result = mKeyboardHandler->VOnKeyUp(msg.pEvent->key.keysym.sym);
            }
            break;
            
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            if (mPointerHandler)
            {
                std::string button = msg.pEvent->button.button == SDL_BUTTON_LEFT ? "PointerLeft" : "PointerRight";
                result = mPointerHandler->VOnPointerButtonDown(Point(msg.pEvent->button.x, msg.pEvent->button.y), mPointerRadius, button);
            }
            break;
            
        case SDL_MOUSEMOTION:
            if (mPointerHandler)
                result = mPointerHandler->VOnPointerMove(Point(msg.pEvent->button.x, msg.pEvent->button.y), mPointerRadius);
            break;
            
        default:
            break;
    }
    
    return result;
}

}
