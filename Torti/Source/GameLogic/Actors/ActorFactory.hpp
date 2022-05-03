//
//  ActorFactory.hpp
//  Pong
//
//  Created by John Geiger on 3/31/22.
//
#pragma once

#ifndef ActorFactory_hpp
#define ActorFactory_hpp

#include "tinyxml2.h"
#include "Math.hpp"
#include "GenericObjectFactory.hpp"
#include "XmlResourceLoader.hpp"
#include "ActorInterfaces.hpp"

namespace Torti {

class ActorFactory
{
    ActorId mLastActorId;
    
protected:
    GenericObjectFactory<ActorComponent, ComponentId> mComponentFactory;
    
public:
    ActorFactory();
    
    StrongActorPtr CreateActor(const std::string actorResource, XmlElementPtr overrides, const Point* initialTransform, const ActorId serversActorId = INVALID_ACTOR_ID);
    void ModifyActor(StrongActorPtr pActor, XmlElementPtr overrides);
    
protected:
    // [rez] This function can be overridden by a subclass so you can create game-specific C++ components.  If you do
    // this, make sure you call the base-class version first.  If it returns NULL, you know it's not an engine component.
    virtual StrongActorComponentPtr VCreateComponent(XmlElementPtr pData);
    
private:
    ActorId GetNextActorId() { ++mLastActorId; return mLastActorId; }
};

}

#endif /* ActorFactory_hpp */
