//
//  EventManagerExample.cpp
//
//  Shows an example of using the Event Manager class
//
//  Created by John Geiger on 3/2/22.
//

//#include <iostream>
//#include <chrono>
//#include <thread>
//#include "Math.hpp"
//#include "SDLWindow.hpp"
//#include "SDLRenderer.hpp"
//#include "EventManager.hpp"
//
//class Example
//{
//public:
//    Example()
//    {
//        Torti::EventListenerDelegate d = fastdelegate::MakeDelegate(this, &Example::ExampleDelegate);
//        
//        Torti::IEventManager::GetGlobalEventManager()->VAddListener(d, Torti::EventData_EnvironmentLoaded::sk_EventType);
//    }
//    ~Example()
//    {
//        // Essentially need to do this because we have no reference to our delegate;
//        // Could keep one, but we'd rather incur a performance hit during shutdown
//        // than a memory hit during program execution
//        Torti::EventListenerDelegate d = fastdelegate::MakeDelegate(this, &Example::ExampleDelegate);
//        
//        Torti::IEventManager::GetGlobalEventManager()->VRemoveListener(d, Torti::EventData_EnvironmentLoaded::sk_EventType);
//    }
//    
//    void ExampleDelegate(Torti::IEventDataPtr pEventData);
//};
//
//void Example::ExampleDelegate(Torti::IEventDataPtr pEventData)
//{
//    // Cast to actual event data we need
//    std::shared_ptr<Torti::EventData_EnvironmentLoaded> pCastEventData = std::static_pointer_cast<Torti::EventData_EnvironmentLoaded>(pEventData);
//    
//    printf("Environment loaded");
//}
//
//std::shared_ptr<Torti::SDLWindow> InitWindow()
//{
//    std::shared_ptr<Torti::SDLWindow> window(new Torti::SDLWindow());
//    window->VCreateWindow("", 0, 0, 500, 500);
//    return window;
//}
//
//Torti::SDLRenderer* InitRenderer(const std::shared_ptr<Torti::IWindow> window)
//{
//    Torti::SDLRenderer* renderer = new Torti::SDLRenderer();
//    renderer->VInitRenderer(window);
//    return renderer;
//}
//
//Torti::EventManager* InitEventManager()
//{
//    Torti::EventManager* eventManager = new Torti::EventManager("Global", true);
//    return eventManager;
//}
//
//void Render(Torti::IRenderer* renderer)
//{
//    renderer->VPreRender();
//    renderer->VDrawLine(Torti::Point(0, 0), Torti::Point(30, 30), Torti::Color(0, 0, 0, 0));
//    renderer->VPostRender();
//}
//
//int main(int argc, const char * argv[]) {
//    SDL_Init(SDL_INIT_VIDEO);
//    
//    std::shared_ptr<Torti::IWindow> window = InitWindow();
//    Torti::IRenderer* renderer = InitRenderer(window);
//    Torti::EventManager* gEventManager = InitEventManager();
//    
//    // Register event delegate
//    Example* ex = new Example();
//    
//    // Create and queue event
//    std::shared_ptr<Torti::EventData_EnvironmentLoaded> pEnvLoadedEvent(new Torti::EventData_EnvironmentLoaded());
//    gEventManager->VQueueEvent(pEnvLoadedEvent);
//        
//    SDL_Event event; bool isQuitting = false;
//    while (!isQuitting)
//    {
//        if (SDL_PollEvent(&event) != 0)
//        {
//            if (event.type == SDL_QUIT)
//            {
//                isQuitting = true;
//            }
//        }
//        
//        gEventManager->VTickVUpdate();
//        Render(renderer);
//    }
//    
//    renderer->VShutdown();
//    delete renderer;
//    renderer = NULL;
//    window->VShutdown();
//    window = NULL;
//    return 0;
//}
//
