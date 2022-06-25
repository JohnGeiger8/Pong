//
//  ActorFactory.cpp
//  Pong
//
//  Created by John Geiger on 3/31/22.
//

#include "ActorFactory.hpp"
#include "Actor.hpp"
#include "ActorComponent.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"

namespace Torti {

ActorFactory::ActorFactory()
{
    mLastActorId = INVALID_ACTOR_ID;
    
    // Register components
    mComponentFactory.Register<TransformComponent>(ActorComponent::GetIdFromName(TransformComponent::gName));
    mComponentFactory.Register<PhysicsComponent>(ActorComponent::GetIdFromName(PhysicsComponent::gName));
}

StrongActorPtr ActorFactory::CreateActor(const std::string actorResource, XmlElementPtr overrides, const Point *initialTransform, const ActorId serversActorId)
{
    // Grab the root XML node
    XmlElementPtr pRoot = XmlResourceLoader::LoadAndReturnRootXmlElement(actorResource.c_str());
    if (!pRoot)
    {
        printf("Failed to create actor from resource: %s", actorResource.c_str());
        return StrongActorPtr();
    }

    // create the actor instance
    ActorId nextActorId = serversActorId;
    if (nextActorId == INVALID_ACTOR_ID)
    {
        nextActorId = GetNextActorId();
    }
    StrongActorPtr pActor(new Actor(GetNextActorId()));
    if (!pActor->Init(pRoot))
    {
        printf("Failed to initialize actor: %s", actorResource.c_str());
        return StrongActorPtr();
    }

    bool initialTransformSet = false;

    // Loop through each child element and load the component
    for (XmlElementPtr pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
    {
        StrongActorComponentPtr pComponent(VCreateComponent(pNode));
        if (pComponent)
        {
            pActor->AddComponent(pComponent);
            pComponent->SetOwner(pActor);
        }
        else
        {
            // If an error occurs, we kill the actor and bail.  We could keep going, but the actor is will only be
            // partially complete so it's not worth it.  Note that the pActor instance will be destroyed because it
            // will fall out of scope with nothing else pointing to it.
            return StrongActorPtr();
        }
    }

    if (overrides)
    {
        ModifyActor(pActor, overrides);
    }

    // FIXME: figure this out
    // This is a bit of a hack to get the initial transform of the transform component set before the
    // other components (like PhysicsComponent) read it.
//    std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::g_Name));
//    if (pInitialTransform && pTransformComponent)
//    {
//        pTransformComponent->SetPosition(pInitialTransform->GetPosition());
//    }

    // Now that the actor has been fully created, run the post init phase
    pActor->PostInit();

    return pActor;
}

// FIXME: implement
void ActorFactory::ModifyActor(StrongActorPtr pActor, tinyxml2::XMLElement* overrides)
{
    
}

///
/// Creates component to be attached to Actor
///
/// @Param pData points to XMLElement data of component
/// @Returns StrongActorComponentPointer to newly created component, empty pointer otherwise
///
StrongActorComponentPtr ActorFactory::VCreateComponent(XmlElementPtr pData)
{
    const char* name = pData->Value();
    StrongActorComponentPtr pComponent(mComponentFactory.Create(ActorComponent::GetIdFromName(name)));

    // initialize the component if we found one
    if (pComponent)
    {
        if (!pComponent->VInit(pData))
        {
            printf("Component failed to initialize: %s", name);
            return StrongActorComponentPtr();
        }
    }
    else
    {
        printf("Couldn't find ActorComponent named %s", name);
        return StrongActorComponentPtr();  // fail
    }

    // pComponent will be NULL if the component wasn't found.  This isn't necessarily an error since you might have a
    // custom CreateComponent() function in a sub class.
    return pComponent;
}


}
