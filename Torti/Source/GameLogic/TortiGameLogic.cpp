//
//  TortiGameLogic.cpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//

#include "TortiGameLogic.hpp"
#include "TortiHumanView.hpp"
#include "EventManager.hpp"
#include "Globals.hpp"

namespace Torti {

TortiGameLogic::TortiGameLogic()
    : mLifetime(0.0),
        mState(BGS_Initializing),
        mExpectedPlayers(0),
        mHumanPlayersAttached(0)
{
        
}

TortiGameLogic::~TortiGameLogic()
{
    while (!mGameViews.empty())
        mGameViews.pop_front();

}

bool TortiGameLogic::Init()
{
    return true;
}

void TortiGameLogic::VAddView(std::shared_ptr<IGameView> pView)
{
    int viewID = static_cast<int>(mGameViews.size());
    mGameViews.push_front(pView);
    pView->VOnAttach(viewID);
    pView->VOnRestore();
}

void TortiGameLogic::VRemoveView(std::shared_ptr<IGameView> pView)
{
    mGameViews.remove(pView);
}

bool TortiGameLogic::VLoadGame(const char *levelResource)
{
    XmlElementPtr pRoot = XmlResourceLoader::LoadAndReturnRootXmlElement(levelResource);
    if (!pRoot)
    {
        printf("Failed to find level resource file: %s", levelResource);
        return false;
    }
    
    for (const std::shared_ptr<IGameView> &view : mGameViews)
    {
        if (view->VGetType() == GameView_Human)
        {
            std::shared_ptr<TortiHumanView> pHumanView = std::static_pointer_cast<TortiHumanView, IGameView>(view);
            pHumanView->LoadGame(pRoot);
        }
    }
    
    if (!VLoadGameDelegate(pRoot))
        return false;
    
    std::shared_ptr<EventData_EnvironmentLoaded> pNewGameEvent(new EventData_EnvironmentLoaded());
    IEventManager::GetGlobalEventManager()->VTriggerEvent(pNewGameEvent);
    
    return true;
}

void TortiGameLogic::VOnUpdate(float time, float elapsedTime)
{
    int deltaMs = int(elapsedTime * 1000.0f);
    mLifetime += elapsedTime;
    
    switch (mState)
    {
        case BGS_Initializing:
            VChangeState(BGS_MainMenu);
            break;
        
        case BGS_MainMenu:
            break;
            
        case BGS_LoadingGameEnvironment:
            break;
        
        case BGS_Running:
            if (m_pPhysics)
            {
                //FIXME: add these in
//                m_pPhysics->VOnUpdate(elapsedTime);
//                m_pPhysics->VSyncVisibleScene();
            }
            break;
            
        default:
            printf("Unrecognized game state.");
            break;
    }
    
    // Update game views
    for (const std::shared_ptr<IGameView> &view : mGameViews)
    {
        view->VOnUpdate(deltaMs);
    }
}

void TortiGameLogic::VChangeState(BaseGameState newState)
{
    if (newState == BGS_LoadingGameEnvironment)
    {
        mState = newState;
        if (!g_pApp->VLoadGame())
        {
            printf("Game failed to load");
            g_pApp->AbortGame();
        }
        else
        {
            VChangeState(BGS_MainMenu);
        }
    }
}

}
