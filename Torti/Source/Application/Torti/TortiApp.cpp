//
//  TortiApp.cpp
//  Pong
//
//  Created by John Geiger on 3/4/22.
//

#include "TortiApp.hpp"
#include "SDLRenderer.hpp"
#include "SDLWindow.hpp"
#include "Audio.hpp"
#include "Globals.hpp"

namespace Torti {

/// Application global variable
TortiGameApp* g_pApp = NULL;
AudioSystemPtr g_pAudio = NULL;

TortiGameApp::TortiGameApp()
    : m_pGame(NULL),
        mDesktopSize(0, 0, 0, 0),
        mScreenSize(0, 0),
        mIsRunning(false),
        m_pEventManager(NULL),
        m_pWindow(NULL),
        m_pRenderer(NULL),
        mIsQuitRequested(false),
        mIsQuitting(false),
        mResources()
{
    g_pApp = this;
}

///
/// Initialize all major systems of application
///
bool TortiGameApp::InitInstance(int screenWidth, int screenHeight)
{
    RegisterEngineEvents();
    VRegisterGameEvents();
        
    m_pEventManager = std::shared_ptr<EventManager>(new EventManager("", true));
    if (!m_pEventManager)
    {
        printf("Error initializing event manager.\n");
        return false;
    }
    
    m_pWindow = std::make_shared<SDLWindow>();
    if (!m_pWindow->VCreateWindow(VGetGameTitle(), 0, 0, screenWidth, screenHeight))
    {
        printf("Error initializing window of type %d.\n", m_pWindow->VGetWindowType());
        return false;
    }
    
    mScreenSize = Point(screenWidth, screenHeight);
    
    m_pRenderer = std::make_shared<SDLRenderer>();
    if (!m_pRenderer->VInitRenderer(m_pWindow))
    {
        printf("Error initializing renderer.\n");
        return false;
    }
    
    m_pGame = VCreateGameAndView();
    if (!m_pGame)
    {
        printf("Error initializing Game Logic and View.");
        return false;
    }
    
    // FIXME: Load resources we'll need to start game
    
    mIsRunning = true;
    
    return true;
}

bool TortiGameApp::VLoadGame()
{
    return m_pGame->VLoadGame("");
}

///
/// Called once at beginning of every frame. Updates the scene, but doesn't actually render.
///  @Param time current time
///  @Param elapsedTime time elapsed since last frame????????
///
void TortiGameApp::OnUpdateGame(double time, float elapsedTime)
{
    if (g_pApp->mIsQuitting)
    {
        const IEventDataPtr pQuitEvent = std::shared_ptr<IEventData>(new EventData_QuittingGame());
        IEventManager::GetGlobalEventManager()->VQueueEvent(pQuitEvent);
    }
    
    if (g_pApp->m_pGame)
    {
        // Give event queue 20 ms to process events
        IEventManager::GetGlobalEventManager()->VTickVUpdate(20);
        
        g_pApp->m_pGame->VOnUpdate(time, elapsedTime);
    }
}

///
/// Performs  all of scene's rendering. Called at end of each frame, or when window needs redrawing
///
void TortiGameApp::OnFrameRender(double time, float elapsedTime)
{
    TortiGameLogic *pGame = g_pApp->m_pGame.get();
    
    for (std::shared_ptr<IGameView> view : pGame->mGameViews)
    {
        view->VOnRender(time, elapsedTime);
    }
}

bool TortiGameApp::ProcessMessages()
{
    // FIXME: implement
    /*
     Check out GameCodeApp::msgProc()
     Maybe create IMessageHandler member function that allows us to handle message depending on SDL vs. some other thing being used
     Either way, this is where the SDL Event is grabbed and sent to the list of game views
     */
    SDL_EventPtr pEvent;
    while (!mIsQuitting)
    {
        if (SDL_PollEvent(pEvent.get()) != 0)
        {
            switch (pEvent->type) {
                case SDL_QUIT:
                    mIsQuitting = true;
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                case SDL_KEYMAPCHANGED:
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                case SDL_CONTROLLERBUTTONUP:
                case SDL_CONTROLLERBUTTONDOWN:
                case SDL_CONTROLLERAXISMOTION:
                case SDL_CONTROLLERTOUCHPADUP:
                case SDL_CONTROLLERTOUCHPADDOWN:
                case SDL_CONTROLLERTOUCHPADMOTION:
                case SDL_CONTROLLERDEVICEADDED:
                case SDL_CONTROLLERDEVICEREMOVED:
                case SDL_CONTROLLERSENSORUPDATE:
                case SDL_CONTROLLERDEVICEREMAPPED:
                    if (g_pApp->m_pGame)
                    {
                        std::shared_ptr<TortiGameLogic> game = g_pApp->m_pGame;
                        AppMessage message;
                        message.pEvent = pEvent;
                        
                        // Loop through in reverse order b/c top view processes messages first
                        for (GameViewList::reverse_iterator i = game->mGameViews.rbegin(); i != game->mGameViews.rend(); i++)
                        {
                            if ((*i)->VOnAppMessage(message))
                            {
                                // Message processed: break from for loop
                                break;
                            }
                        }
                    }
                default:
                    break;
            }
        }
    }
    
    // FIXME: Handle quitting here?
    
    return true;
}

std::shared_ptr<ResourceHandle> TortiGameApp::GetResourceHandle(const Resource &r)
{
    auto it = mResources.find(r.mName);
    if (it == mResources.end())
        return std::shared_ptr<ResourceHandle>();
    
    return it->second;
}

//// FIXME: development function
//void TortiGameApp::AddResource(std::shared_ptr<ResourceHandle> rh)
//{
//
//}

// Don't think I need this
void TortiGameApp::RegisterEngineEvents()
{
    
}

}
