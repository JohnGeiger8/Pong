//
//  TortiHumanView.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef TortiHumanView_hpp
#define TortiHumanView_hpp

#include "IGameView.hpp"

namespace Torti {

using XmlElementPtr = tinyxml2::XMLElement*;

class TortiHumanView : public IGameView
{
protected:
    GameViewId mViewId;
    
    unsigned int mCurrentTick;      // current time
    unsigned int mLastRender;       // time of last render
    bool mRunFullSpeed;
    
public:
    ScreenElementList mScreenElements;
    //std::shared_ptr<IKeyboardHandler> mKeyboardHandler;
//    std::shared_ptr<IPointerHandler> mPointerHandler;
    //int mPointerRadius;
    
    TortiHumanView();
    virtual ~TortiHumanView();
    
    bool LoadGame(XmlElementPtr pLevelData);

public:
    // IGameView implementation
    virtual void VOnRender(double fTime, float fElapsedTime);
    virtual void VOnRestore();
    virtual void VOnLostDevice();
    virtual GameViewType VGetType() { return GameView_Human; };
    virtual GameViewId VGetId() const { return mViewId; };
    virtual void VOnAttach(GameViewId vid) { mViewId = vid; }
    
    virtual void VPushElement(ScreenElementPtr pElement);
    virtual void VRemoveElement(ScreenElementPtr pElement);
    
    void TogglePause(bool active);
    
    bool InitAudio();
    
    // Camera adjustments
//    virtual void VSetCameraOffset(const Vec4 & camOffset) { }

//    virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;
    virtual void VOnUpdate(unsigned long deltaMs);
    
protected:
    virtual bool VLoadGameDelegate(XmlElementPtr pLevelData) { return true; }
};

}

#endif /* TortiHumanView_hpp */
