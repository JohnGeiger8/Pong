//
//  ActorInterfaces.hpp
//  Pong
//
//  Created by John Geiger on 4/24/22.
//
#pragma once

#ifndef ActorInterfaces_hpp
#define ActorInterfaces_hpp

#include <memory>
#include <string>
#include "tinyxml2.h"

namespace Torti {

class Actor;
class ActorComponent;

using ActorId = unsigned int;
using ComponentId = unsigned int;
using ActorType = std::string;

const ActorId INVALID_ACTOR_ID = 0;
const ComponentId INVALID_COMPONENT_ID = 0;

using StrongActorPtr = std::shared_ptr<Actor>;
using WeakActorPtr = std::weak_ptr<Actor>;
using StrongActorComponentPtr = std::shared_ptr<ActorComponent>;
using WeakActorComponentPtr = std::shared_ptr<ActorComponent>;

using XmlElementPtr = tinyxml2::XMLElement*;

}

#endif /* ActorInterfaces_hpp */
