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
    virtual void VOnRender(double fTime, float fElapsedTime)=0;
    virtual GameViewType VGetType()=0;
    virtual GameViewId VGetId() const=0;
    virtual void VOnAttach(GameViewId vid, ActorId aid)=0;

//    virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;
    virtual void VOnUpdate(unsigned long deltaMs)=0;

    virtual ~IGameView() { };
};

using ScreenElementList = std::list<std::shared_ptr<IScreenElement>>;
using GameViewList = std::list<std::shared_ptr<IGameView>>;

}

#endif /* IGameView_hpp */
