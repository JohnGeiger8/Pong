//
//  PhysicsComponent.cpp
//  Pong
//
//  Created by John Geiger on 5/25/22.
//

#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"
#include "Actor.hpp"
#include "MakeStrongPtr.hpp"

namespace Torti {

// all times are units-per-second
const float DEFAULT_MAX_VELOCITY = 7.5f;
const float DEFAULT_MAX_ANGULAR_VELOCITY = 1.2f;

const char * PhysicsComponent::gName = "PhysicsComponent";

PhysicsComponent::PhysicsComponent()
    : mAcceleration(0.0f),
        mAngularAcceleration(0.0f),
        mMaxVelocity(DEFAULT_MAX_VELOCITY),
        mMaxAngularVelocity(DEFAULT_MAX_ANGULAR_VELOCITY),
        mRigidBodyLocation(0.0f, 0.0f),
        mRigidBodyOrientation(0.0f, 0.0f),
        mRigidBodyScale(1.0f, 1.0f)
{ }

PhysicsComponent::~PhysicsComponent()
{
    m_pGamePhysics->VRemoveActor(m_pOwner->GetId());
}

/* ActorComponent interface */

bool PhysicsComponent::VInit(XmlElementPtr pData)
{
    assert(("VInit not implemented", false));

    return true;
}

void PhysicsComponent::VPostInit()
{
    assert(("VPostInit not implemented", false));

}

void PhysicsComponent::VUpdate(int deltaMs)
{
    assert(("VUpdate not implemented", false));
}

/* Physics Functions */

void PhysicsComponent::ApplyForce(const Vector &direction, float forceNewtons)
{
    m_pGamePhysics->VApplyForce(direction, forceNewtons, m_pOwner->GetId());
}

void PhysicsComponent::ApplyTorque(const Vector &direction, float forceNewtons)
{
    m_pGamePhysics->VApplyTorque(direction, forceNewtons, m_pOwner->GetId());
}

bool PhysicsComponent::KinematicMove(const Mat2x2 &transform)
{
    return m_pGamePhysics->VKinematicMove(transform, m_pOwner->GetId());
}

///
/// Set acceleration of component
/// @Param acceleration acceleration we want object to have
///
void PhysicsComponent::SetAcceleration(float acceleration)
{
    mAcceleration = acceleration;
}

///
/// Make acceleration of component 0
///
void PhysicsComponent::RemoveAcceleration()
{
    mAcceleration = 0;
}

///
/// Set angular acceleration of component
/// @Param acceleration angular acceleration we want object to have
///
void PhysicsComponent::ApplyAngularAcceleration(float acceleration)
{
    mAngularAcceleration = acceleration;
}

///
/// Make angular acceleration of component 0
///
void PhysicsComponent::RemoveAngularAcceleration()
{
    mAngularAcceleration = 0;
}

Vector PhysicsComponent::GetVelocity()
{
    return m_pGamePhysics->VGetVelocity(m_pOwner->GetId());
}

void PhysicsComponent::SetVelocity(const Vector& velocity)
{
    m_pGamePhysics->VSetVelocity(m_pOwner->GetId(), velocity);
}

void PhysicsComponent::RotateY(float angleRadians)
{
    std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::gName));
    
    if (pTransformComponent)
    {
        Mat2x2 transform = pTransformComponent->GetTransform();
        Vector position = transform.GetPosition();

        Mat2x2 rotateY;
        rotateY.BuildRotationY(angleRadians);
        rotateY.SetPosition(position);

        KinematicMove(rotateY);
    }
    else
        printf("Attempting to call RotateY() on actor with no transform component\n");
}

void PhysicsComponent::SetPosition(float x, float y)
{
    std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(m_pOwner->GetComponent<TransformComponent>(TransformComponent::gName));
    if (pTransformComponent)
    {
        Mat2x2 transform = pTransformComponent->GetTransform();
        Vector position = Vector(x, y);
        transform.SetPosition(position);

        KinematicMove(transform);
    }
    else
        printf("Attempting to call RotateY() on actor with no trnasform component\n");
}

void PhysicsComponent::Stop(void)
{
    return m_pGamePhysics->VStopActor(m_pOwner->GetId());
}

}
