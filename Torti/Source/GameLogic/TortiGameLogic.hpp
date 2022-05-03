//
//  TortiGameLogic.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef TortiGameLogic_hpp
#define TortiGameLogic_hpp

#include <map>
#include "tinyxml2.h"
#include "IGameView.hpp"
#include "IGameLogic.hpp"
#include "EventData.hpp"
#include "ActorFactory.hpp"
#include "Math.hpp"

namespace Torti {

using ActorMap = std::map<ActorId, StrongActorPtr>;
using Level = std::string;

class TortiGameLogic : public IGameLogic
{
protected:
    float mLifetime;                           //indicates how long this game has been in session
//    ProcessManager* m_pProcessManager;             // a game logic entity
//    GCCRandom m_random;                                // our RNG
    ActorMap mActors;
    ActorId mLastActorId;
    BaseGameState mState;                            // game state: loading, running, etc.
    int mExpectedPlayers;                            // how many local human players
//    int m_ExpectedRemotePlayers;                    // expected remote human players
//    int m_ExpectedAI;                                // how many AI players
    int mHumanPlayersAttached;
//    int mAIPlayersAttached;
//    int mHumanGamesLoaded;
    GameViewList mGameViews;                        // views that are attached to our game
//    std::shared_ptr<PathingGraph> m_pPathingGraph;        // the pathing graph
    ActorFactory* m_pActorFactory;
    
//    bool m_bProxy;                                    // set if this is a proxy game logic, not a real one
//    int m_remotePlayerId;                            // if we are a remote player - what is out socket number on the server

//    bool m_RenderDiagnostics;                        // Are we rendering diagnostics?
    std::shared_ptr<IGamePhysics> m_pPhysics;

//    LevelManager* m_pLevelManager;                    // Manages loading and chaining levels

public:

    TortiGameLogic();
    virtual ~TortiGameLogic();
    bool Init(void);
//
//    void SetProxy(bool isProxy)
//    {
//        m_bProxy = isProxy;
//    }
//    const bool IsProxy() const { return m_bProxy; }
    
//    const bool CanRunLua() const { return !IsProxy() || GetState()!=BGS_Running; }

    ActorId GetNewActorID(void)
    {
        return ++mLastActorId;
    }
    
//    std::shared_ptr<PathingGraph> GetPathingGraph(void) { return m_pPathingGraph; }
//    GCCRandom& GetRNG(void) { return m_random; }

    virtual void VAddView(std::shared_ptr<IGameView> pView, ActorId actorId=INVALID_ACTOR_ID);
    virtual void VRemoveView(std::shared_ptr<IGameView> pView);

    virtual StrongActorPtr VCreateActor(const std::string &actorResource, tinyxml2::XMLElement *overrides, const Point initialTransform, const ActorId serversActorId=INVALID_ACTOR_ID);  // [rez] note: don't store this strong pointer outside of this class
    virtual void VDestroyActor(const ActorId actorId);
    virtual WeakActorPtr VGetActor(const ActorId actorId);
    virtual void VModifyActor(const ActorId actorId, tinyxml2::XMLElement *overrides);

    virtual void VMoveActor(const ActorId id, Point const &point) {}

    // editor functions
//    std::string GetActorXml(const ActorId id);

    // Level management
//    const LevelManager* GetLevelManager() { return m_pLevelManager; }
    virtual bool VLoadGame(const char* levelResource) override;  // [rez] Subclasses shouldn't override this function; use VLoadGameDelegate() instead
//    virtual void VSetProxy();

    // Logic Update
    virtual void VOnUpdate(float time, float elapsedTime);

    // Changing Game Logic State
    virtual void VChangeState(BaseGameState newState);
    const BaseGameState GetState() const { return mState; }

    // Render Diagnostics
//    void ToggleRenderDiagnostics() { m_RenderDiagnostics = !m_RenderDiagnostics; }
//    virtual void VRenderDiagnostics();
    virtual std::shared_ptr<IGamePhysics> VGetGamePhysics(void) { return m_pPhysics; }
    
//    void AttachProcess(StrongProcessPtr pProcess) { if (m_pProcessManager) {m_pProcessManager->AttachProcess(pProcess);} }

    // event delegates
    void RequestDestroyActorDelegate(IEventDataPtr pEventData);

protected:
    virtual ActorFactory* VCreateActorFactory(void);

    // [rez] Override this function to do any game-specific loading.
    virtual bool VLoadGameDelegate(tinyxml2::XMLElement* pLevelData) { return true; }

    void MoveActorDelegate(IEventDataPtr pEventData);
    void RequestNewActorDelegate(IEventDataPtr pEventData);
};

}

#endif /* TortiGameLogic_hpp */
