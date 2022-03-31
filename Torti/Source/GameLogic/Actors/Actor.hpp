//
//  Actor.hpp
//  Pong
//
//  Created by John Geiger on 3/31/22.
//
#pragma once

#ifndef Actor_hpp
#define Actor_hpp

#include <memory>

namespace Torti {

class Actor;
class ActorComponent;

using ActorId = unsigned int;
using ComponentId = unsigned int;

const ActorId INVALID_ACTOR_ID = 0;
const ComponentId INVALID_COMPONENT_ID = 0;

using StrongActorPtr = std::shared_ptr<Actor>;
using WeakActorPtr = std::weak_ptr<Actor>;
using StrongActorComponentPtr = std::shared_ptr<ActorComponent>;
using WeakActorComponentPtr = std::shared_ptr<ActorComponent>;

}

#endif /* Actor_hpp */
