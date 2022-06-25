//
//  PhysicsComponent.hpp
//  Pong
//
//  Created by John Geiger on 5/25/22.
//
#pragma once

#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "ActorComponent.hpp"
#include "Math.hpp"
#include "IPhysics.hpp"

namespace Torti {

class PhysicsComponent : public ActorComponent
{
public:
    const static char *gName;
    virtual const char *VGetName() const override { return PhysicsComponent::gName; }

public:
    PhysicsComponent();
    virtual ~PhysicsComponent();

    // ActorComponent interface
    virtual bool VInit(XmlElementPtr pData) override;
    virtual void VPostInit() override;
    virtual void VUpdate(int deltaMs) override;

    // Physics functions
    void ApplyForce(const Vector& direction, float forceNewtons);
    void ApplyTorque(const Vector& direction, float forceNewtons);
    bool KinematicMove(const Mat2x2& transform);

    // acceleration
    void SetAcceleration(float acceleration);
    void RemoveAcceleration();
    void ApplyAngularAcceleration(float acceleration);
    void RemoveAngularAcceleration();

    Vector GetVelocity();
    void SetVelocity(const Vector& velocity);
    void RotateY(float angleRadians);
    void SetPosition(float x, float y);
    void Stop();


protected:
    void CreateShape();
    void BuildRigidBodyTransform(XmlElementPtr pTransformElement);

    float mAcceleration, mAngularAcceleration;
    float mMaxVelocity, mMaxAngularVelocity;

    std::string mShape;
    std::string mDensity;
    std::string mMaterial;
    
    // Not world position - this is how the rigid body is offset from the position of the actor.
    Vector mRigidBodyLocation;
    Vector mRigidBodyOrientation;      // same as above, but orientation
    Vector mRigidBodyScale;            // same as above, but scale
    
    std::shared_ptr<IGamePhysics> m_pGamePhysics;  // might be better as a weak ptr...
};

}

#endif /* PhysicsComponent_hpp */
