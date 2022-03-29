//
//  IPhysics.hpp
//  Pong
//
//  Created by John Geiger on 3/27/22.
//
#pragma once

#ifndef IPhysics_hpp
#define IPhysics_hpp

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
//    virtual void VAddSphere(float radius, WeakActorPtr actor, /*const Mat4x4& initialTransform, */const std::string& densityStr, const std::string& physicsMaterial)=0;
//    virtual void VAddBox(const Vec3& dimensions, WeakActorPtr gameActor, /*const Mat4x4& initialTransform, */ const std::string& densityStr, const std::string& physicsMaterial) = 0;
//    virtual void VAddPointCloud(Vec3 *verts, int numPoints, WeakActorPtr gameActor, /*const Mat4x4& initialTransform, */ const std::string& densityStr, const std::string& physicsMaterial)=0;
//    virtual void VRemoveActor(ActorId id)=0;

    // Debugging
//    virtual void VRenderDiagnostics() = 0;

    // Physics world modifiers
//    virtual void VCreateTrigger(WeakActorPtr pGameActor, const Vec3 &pos, const float dim)=0;
//    virtual void VApplyForce(const Vec3 &dir, float newtons, ActorId aid)=0;
//    virtual void VApplyTorque(const Vec3 &dir, float newtons, ActorId aid)=0;
//    virtual bool VKinematicMove(const Mat4x4 &mat, ActorId aid)=0;
//
//    // Physics actor states
//    virtual void VRotateY(ActorId actorId, float angleRadians, float time) = 0;
//    virtual float VGetOrientationY(ActorId actorId) = 0;
//    virtual void VStopActor(ActorId actorId) = 0;
//    virtual Vec3 VGetVelocity(ActorId actorId) = 0;
//    virtual void VSetVelocity(ActorId actorId, const Vec3& vel) = 0;
//    virtual Vec3 VGetAngularVelocity(ActorId actorId) = 0;
//    virtual void VSetAngularVelocity(ActorId actorId, const Vec3& vel) = 0;
//    virtual void VTranslate(ActorId actorId, const Vec3& vec) = 0;
//
//    virtual void VSetTransform(const ActorId id, const Mat4x4& mat) = 0;
//    virtual Mat4x4 VGetTransform(const ActorId id) = 0;

    virtual ~IGamePhysics() { };
};

}
#endif /* IPhysics_hpp */
