//
//  TortiApp.hpp
//  Pong
//
//  Created by John Geiger on 3/4/22.
//
#pragma once
#ifndef TortiApp_hpp
#define TortiApp_hpp

#include <memory>

namespace Torti {


using String = std::string;

//class TortiGameApp
//{
//protected:
//    bool mIsRunning;          // Everything is initialized and game is in main loop
//    bool mIsQuitRequested;      // App should run the close sequence
//    bool mIsQuitting;           // App is running close sequence
//    Rect mDesktopSize;          // Current desktop size, not client window size
//    Point mScreenSize;          // Game screen size
//
//public:
//    TortiGameApp();
//
//    virtual bool InitInstance(int screenWidth = 600, int screenHeight = 600);
//
//    virtual String VGetGameTitle()=0;
//
//    bool OnClose();
//
//    std::shared_ptr<IRenderer> m_pRenderer;
//    std::shared_ptr<IWindow> m_pWindow;
//    TortiGameLogic* m_pGame;
//    std::shared_ptr<EventManager> m_pEventManager;
//    struct GameOptions mGameOptions;
//
//    // Must be overridden
//    virtual std::shared_ptr<TortiGameLogic> VCreateGameAndView()=0;
//    virtual bool VLoadGame();
//
//    // Main Loop stuff
//    void AbortGame() { m_bQuitting = true; }
//    bool IsRunning() { return m_bIsRunning; }
//    void SetQuitting(bool quitting) { m_bQuitting = quitting; }
//
//    bool LoadStrings(String language);
//
//    void OnUpdateGame(double time, float elapsedTime);
//    void OnFrameRender(double time, float elapsedTime);
//
//    std::shared_ptr<TortiGameLogic> GetGameLogic(void) const { return m_pGame; }
//
//protected:
//    virtual void VRegisterGameEvents() { }
//
//private:
//    void RegisterEngineEvents();
//};
//
//extern TortiGameApp *g_pApp;

}

#endif /* TortiApp_hpp */
