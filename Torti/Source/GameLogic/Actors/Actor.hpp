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
#include <map>
#include "tinyxml2.h"
#include "ActorInterfaces.hpp"
#include "ActorComponent.hpp"

namespace Torti {
// FIXME: Untested

///
/// Defines any game entity
///
class Actor
{
    friend class ActorFactory;
        
    using ActorComponents = std::map<ComponentId, StrongActorComponentPtr>;

    ActorId mId;
    ActorComponents mComponents;
    ActorType mType;
    
public:
    explicit Actor(ActorId id);
    ~Actor();
    
    bool Init(XmlElementPtr pData);
    void PostInit();
    void Destroy();
    void Update(int deltaMs);
    
    // Accessors
    ActorId GetId() const { return mId; }
    
    // Template function for getting components
    template <class ComponentType>
    std::weak_ptr<ComponentType> GetComponent(ComponentId id)
    {
        ActorComponents::iterator findIt = mComponents.find(id);
        if (findIt != mComponents.end())
        {
            StrongActorComponentPtr pBase(findIt->second);
            // Cast to subclass version of pointer
            std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));
            
            std::weak_ptr<ComponentType> pWeakSub(pSub); // Convert strong to weak pointer
            
            return pWeakSub;
        }
        else
        {
            return std::weak_ptr<ComponentType>();
        }
    }
    
    template <class ComponentType>
    std::weak_ptr<ComponentType> GetComponent(const char *name)
    {
        ComponentId id = ActorComponent::GetIdFromName(name);
        ActorComponents::iterator findIt = mComponents.find(id);
        if (findIt != mComponents.end())
        {
            StrongActorComponentPtr pBase(findIt->second);
            std::shared_ptr<ComponentType> pSub(static_pointer_cast<ComponentType>(pBase));  // cast to subclass version of the pointer
            std::weak_ptr<ComponentType> pWeakSub(pSub);  // convert strong pointer to weak pointer
            return pWeakSub;  // return the weak pointer
        }
        else
        {
            return std::weak_ptr<ComponentType>();
        }
    }
    
private:
    // Only the Actor Factory adds components
    void AddComponent(StrongActorComponentPtr pComponent);
};

}

#endif /* Actor_hpp */
