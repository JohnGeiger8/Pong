//
//  ActorComponent.hpp
//  Pong
//
//  Created by John Geiger on 4/24/22.
//
#pragma once

#ifndef ActorComponent_hpp
#define ActorComponent_hpp

#include <functional>
#include "tinyxml2.h"
#include "ActorInterfaces.hpp"

namespace Torti {

///
/// Defines a component to be attached to an actor
///
class ActorComponent
{
    // FIXME: Untested
    friend class ActorFactory;
    
protected:
    StrongActorPtr m_pOwner;
    
public:
    virtual ~ActorComponent() { }
    
    // Override by component implementation classes
    virtual bool VInit(tinyxml2::XMLElement* pData) = 0;
    virtual void VPostInit() { }
    virtual void VUpdate(int deltaMs) { }
    
    virtual ComponentId VGetComponentId() const = 0;
    virtual const char *VGetName() const = 0;
    
    // FIXME: this seems wrong currently
    static ComponentId GetIdFromName(const char* componentStr)
    {
//        void* rawId = std::HashedString::hash_name(componentStr);
//        return reinterpret_cast<ComponentId>(componentStr)
        return 0;
    }

private:
    void SetOwner(StrongActorPtr pOwner) { m_pOwner = pOwner; }
};

}
#endif /* ActorComponent_hpp */
