//
//  PongApp.cpp
//  Pong
//
//  Created by John Geiger on 3/20/22.
//

#include "PongApp.hpp"

namespace Pong {

PongApp g_pPongApp;

PongApp::PongApp()
{
    
}

String PongApp::VGetGameTitle()
{
    return "Pong";
}

std::shared_ptr<Torti::TortiGameLogic> PongApp::VCreateGameAndView()
{
    // FIXME: implement/document
    
    return std::shared_ptr<Torti::TortiGameLogic>();
}

void PongApp::VRegisterGameEvents()
{
    // FIXME: implement/document
}

}
