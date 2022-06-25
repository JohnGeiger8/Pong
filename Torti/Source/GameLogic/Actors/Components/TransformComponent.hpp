//
//  TransformComponent.hpp
//  Pong
//
//  Created by John Geiger on 6/1/22.
//
#pragma once

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include "ActorInterfaces.hpp"
#include "ActorComponent.hpp"
#include "Math.hpp"

namespace Torti {

///
/// This component implementation is a very simple representation of the
/// physical aspect of an actor.  It just defines the transform and doesn't
/// register with the physics system at all.
///
class TransformComponent : public ActorComponent
{
    Mat2x2 mTransform;
    
public:
    const static char *gName;
    virtual const char *VGetName() const override { return TransformComponent::gName; }
    
    TransformComponent() : mTransform(Mat2x2::gIdentity) { }
    
    // transform functions
    inline Mat2x2 GetTransform() const { return mTransform; }
    inline void SetTransform(const Mat2x2& newTransform);
    inline Vector GetPosition() const;
    inline void SetPosition(const Vector pos);
    inline Vector GetLookAt() const;
    
public:
    // ActorComponent interface
    virtual bool VInit(XmlElementPtr pData) override;
    virtual void VPostInit() override;
    virtual void VUpdate(int deltaMs) override;

};

inline void TransformComponent::SetTransform(const Mat2x2 &newTransform)
{
    mTransform = newTransform;
}

inline void TransformComponent::SetPosition(const Vector pos)
{
    mTransform.SetPosition(pos);
};

inline Vector TransformComponent::GetPosition() const
{
    return mTransform.GetPosition();
};

inline Vector TransformComponent::GetLookAt() const
{
    return mTransform.GetDirection();
};

}

#endif /* TransformComponent_hpp */
