//
//  PongLogic.hpp
//  Pong
//
//  Created by John Geiger on 7/4/22.
//
#pragma once

#ifndef PongLogic_hpp
#define PongLogic_hpp

#include "TortiGameLogic.hpp"

namespace Pong {

class PongLogic : public Torti::TortiGameLogic
{
public:
    PongLogic();
    virtual ~PongLogic();
    
    // Overloads
    virtual void VChangeState(Torti::BaseGameState newState) override;
    
    // Event Delegates
    void RequestStartGameDelegate(Torti::IEventDataPtr pEventData);
    void EnvironmentLoadedDelegate(Torti::IEventDataPtr pEventData);
    
protected:
    virtual bool VLoadGameDelegate(Torti::XmlElementPtr pLevelData) override;
private:
    void RegisterAllDelegates();
    void RemoveAllDelegate();
    
};

}
#endif /* PongLogic_hpp */
