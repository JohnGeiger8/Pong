//
//  IGameView.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef IGameView_hpp
#define IGameView_hpp

#include <list>
#include "ActorInterfaces.hpp"
#include "IScreenElement.hpp"
#include "AppMessage.hpp"

namespace Torti {

using GameViewId = unsigned int;

enum GameViewType
{
    GameView_Human,
    GameView_Remote,
    GameView_AI,
    GameView_Recorder,
    GameView_Other
};

class IGameView
{
public:
    virtual void VOnRestore()=0;
    virtual void VOnLostDevice()=0;
    virtual void VOnRender(double fTime, float fElapsedTime)=0;
    virtual GameViewType VGetType()=0;
    virtual GameViewId VGetId() const=0;
    
    virtual void VOnAttach(GameViewId vid)=0;//, ActorId aid)=0;

    ///
    /// Processes Application Message
    /// @Returns true if the view has consumed the message, meaning no other view should process it
    /// 
    virtual bool VOnAppMessage(AppMessage msg)=0;
    virtual void VOnUpdate(unsigned long deltaMs)=0;

    virtual ~IGameView() { };
};

using ScreenElementPtr = std::shared_ptr<IScreenElement>;
using ScreenElementList = std::list<std::shared_ptr<IScreenElement>>;
using GameViewList = std::list<std::shared_ptr<IGameView>>;

}

#endif /* IGameView_hpp */
