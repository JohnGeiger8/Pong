//
//  WindowAndRendererExample.cpp
//
//  Example of IWindow, SDLWindow, IRenderer, and SDLRenderer classes
//
//  Created by John Geiger on 3/2/22.
//

//#include <iostream>
//#include "SDLWindow.hpp"
//#include "SDLRenderer.hpp"
//
//int main(int argc, const char * argv[]) {
//
//    if (SDL_Init(SDL_INIT_VIDEO) == -1)
//        return -1;
//
//    // Initialize and create window
//    std::shared_ptr<Torti::IWindow> window = std::make_shared<Torti::SDLWindow>();
//    window->VCreateWindow("My window", 0, 0, 300, 300);
//
//    if (window->VGetWindowType() !== Torti::WindowType::SDL2_Window)
//    {
//        printf("Invalid window");
//        return -1;
//    }
//
//    // Initialize and create renderer
//    std::shared_ptr<Torti::IRenderer> renderer = std::make_shared<Torti::SDLRenderer>();
//    renderer->VInitRenderer(window);
//    renderer->VSetBackgroundColor(0, 255, 0, 1);
//
//    Torti::Color bgColor1(0, 0, 255, 1);
//    Torti::Color bgColor2(0, 255, 0, 1);
//    bool chooseColor1 = true;
//    SDL_Event e;
//    while (SDL_WaitEvent(&e))
//    {
//        renderer->VPreRender();
//
//        if (e.type == SDL_QUIT)
//        {
//            renderer->VShutdown();
//            window->VShutdown();
//            SDL_Quit();
//            return 0;
//        }
//        else if (e.type == SDL_MOUSEBUTTONDOWN)
//        {
//            chooseColor1 = !chooseColor1;
//
//            if (chooseColor1)
//                renderer->VSetBackgroundColor(bgColor1.r, bgColor1.g, bgColor1.b, bgColor1.a);
//            else
//                renderer->VSetBackgroundColor(bgColor2.r, bgColor2.g, bgColor2.b, bgColor2.a);
//        }
//        renderer->VDrawLine(Torti::Point(0, 0), Torti::Point(10, 10), Torti::Color(0, 0, 0, 1));
//
//        renderer->VPostRender();
//    }
//
//    return 0;
//}
//
