//
//  TransformComponent.cpp
//  Pong
//
//  Created by John Geiger on 6/1/22.
//

#include "TransformComponent.hpp"

namespace Torti {

const char *TransformComponent::gName = "TransformComponent";

bool TransformComponent::VInit(XmlElementPtr pData)
{
    bool success = false;
    
    return success;
}

void TransformComponent::VPostInit()
{
    assert(("VPostInit not implemented", false));
}

void TransformComponent::VUpdate(int deltaMs)
{
    assert(("VUpdate not implemented", false));
}


}
