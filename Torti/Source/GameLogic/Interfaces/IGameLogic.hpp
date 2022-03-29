//
//  IGameLogic.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef IGameLogic_hpp
#define IGameLogic_hpp

#include <memory>

namespace Torti {

enum BaseGameState
{
    BGS_Invalid,
    BGS_Initializing,
    BGS_MainMenu,
    BGS_LoadingGameEnvironment,
    BGS_Running
};

class IGamePhysics;

class IGameLogic
{
    virtual bool VLoadGame(const char* levelResource)=0;
    virtual void VOnUpdate(float time, float elapsedTime)=0;
    virtual void VChangeState(enum BaseGameState newState)=0;
    virtual std::shared_ptr<IGamePhysics> VGetGamePhysics(void)=0;
};

}

#endif /* IGameLogic_hpp */
