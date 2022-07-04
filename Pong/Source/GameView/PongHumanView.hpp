//
//  PongHumanView.hpp
//  Pong
//
//  Created by John Geiger on 7/4/22.
//
#pragma once

#ifndef PongHumanView_hpp
#define PongHumanView_hpp

#include "TortiHumanView.hpp"

namespace Pong {

class PongHumanView : public Torti::TortiHumanView
{
public:
    PongHumanView();
    virtual ~PongHumanView();
    
//    virtual void VOnMsgProc( AppMsg msg )=0;
    
    virtual void VOnUpdate(unsigned long deltaMs) override;
    virtual void VOnAttach(Torti::GameViewId vid) override;
    
    virtual bool VLoadGameDelegate(Torti::XmlElementPtr pLevelData) override;
    
private:
    void RegisterAllDelegates();
    void RemoveAllDelegates();
};

}

#endif /* PongHumanView_hpp */
