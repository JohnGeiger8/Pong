//
//  IPhysics.hpp
//  Pong
//
//  Created by John Geiger on 3/27/22.
//
#pragma once

#ifndef IPhysics_hpp
#define IPhysics_hpp

#include "ActorInterfaces.hpp"
#include "Math.hpp"

namespace Torti {

///
/// Definition for basic physics
///
class IGamePhysics
{
public:

    // Initialiazation and Maintenance of the Physics World
    virtual bool VInitialize()=0;
    virtual void VSyncVisibleScene() = 0;
    virtual void VOnUpdate(float deltaSeconds) = 0;

    // Initialization of Physics Objects
    virtual void VAddCircle(float radius, WeakActorPtr actor, const std::string& physicsMaterial)=0;
    virtual void VAddRectangle(const Vector& dimensions, WeakActorPtr gameActor, const std::string& physicsMaterial) = 0;
    virtual void VAddPointCloud(Vector *vertices, int numPoints, WeakActorPtr gameActor, const std::string& physicsMaterial)=0;
    virtual void VRemoveActor(ActorId id)=0;

    // Physics world modifiers
    virtual void VCreateTrigger(WeakActorPtr pGameActor, const Vector &position, const float dim)=0;
    virtual void VApplyForce(const Vector &dir, float newtons, ActorId aid)=0;
    virtual void VApplyTorque(const Vector &dir, float newtons, ActorId aid)=0;
    virtual bool VKinematicMove(const Mat2x2 position, ActorId aid)=0;

    // Physics actor states
    virtual void VRotateY(ActorId actorId, float angleRadians, float time) = 0;
    virtual float VGetOrientationY(ActorId actorId) = 0;
    virtual void VStopActor(ActorId actorId) = 0;
    virtual Vector VGetVelocity(ActorId actorId) = 0;
    virtual void VSetVelocity(ActorId actorId, const Vector& vel) = 0;
    virtual Vector VGetAngularVelocity(ActorId actorId) = 0;
    virtual void VSetAngularVelocity(ActorId actorId, const Vector& vel) = 0;
    virtual void VTranslate(ActorId actorId, const Vector& vec) = 0;

    virtual void VSetTransform(const ActorId id, const Point& position) = 0;
    virtual Point VGetTransform(const ActorId id) = 0;

    virtual ~IGamePhysics() { };
};

}
#endif /* IPhysics_hpp */
