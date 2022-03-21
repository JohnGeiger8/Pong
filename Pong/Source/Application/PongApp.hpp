//
//  PongApp.hpp
//  Pong
//
//  Created by John Geiger on 3/20/22.
//
#pragma once

#ifndef PongApp_hpp
#define PongApp_hpp

#include "TortiApp.hpp"

namespace Pong {

using String = std::string;

class PongApp : public Torti::TortiGameApp
{
public:
    PongApp();
    
    virtual String VGetGameTitle();
    
    virtual std::shared_ptr<Torti::TortiGameLogic> VCreateGameAndView();

protected:
    virtual void VRegisterGameEvents();
    
};


}

#endif /* PongApp_hpp */
