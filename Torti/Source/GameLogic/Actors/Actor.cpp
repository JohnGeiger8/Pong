//
//  Actor.cpp
//  Pong
//
//  Created by John Geiger on 3/31/22.
//

#include "Actor.hpp"
#include "ActorComponent.hpp"

namespace Torti {

Actor::Actor(ActorId id)
{
    mId = id;
    mType = "Unknown";
}

///
/// Checks that Destroy was called before actor is deallocated
///
Actor::~Actor()
{
    printf("Destroying actor %u", mId);
    assert(mComponents.empty()); // Was Destroy called first?
}

///
/// Initializes an Actor from XML
///
/// @Param pData points to XMLElement containing actor data
/// @Returns true if successful
///
bool Actor::Init(tinyxml2::XMLElement *pData)
{
    printf("Initializing actor %u", mId);
    
    const char* type = pData->Attribute("type");
    if (!type)
    {
        printf("Failed to initialize actor %u", mId);
        return false;
    }
    mType = type;
    return true;
}

///
/// Runs each of its components PostInit methods
///
void Actor::PostInit()
{
    for (ActorComponents::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        it->second->VPostInit();
    }
}

///
/// Clear all components from actor
///
void Actor::Destroy()
{
    mComponents.clear();
}

///
/// Run each component's update function
///
void Actor::Update(int deltaMs)
{
    for (ActorComponents::iterator it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        it->second->VUpdate(deltaMs);
    }
}

///
/// Add component to Actor
///
void Actor::AddComponent(StrongActorComponentPtr pComponent)
{
    std::pair<ActorComponents::iterator, bool> succeeded = mComponents.insert(std::make_pair(pComponent->VGetComponentId(), pComponent));
    assert(succeeded.second);
}


}
