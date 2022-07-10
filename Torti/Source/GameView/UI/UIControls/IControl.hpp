//
//  IControl.hpp
//  Pong
//
//  Created by John Geiger on 7/8/22.
//
#pragma once

#ifndef IControl_hpp
#define IControl_hpp

#include "Math.hpp"

namespace Torti {

///
/// Interface for any kind of UI Control
/// 
class IControl
{
public:
    virtual void VOnRender(double fTime, float fElapsedTime)=0;
    ///
    /// Called just after class is instantiated, and when interruption such as change in resolution or being awoken from sleep
    ///
    virtual void VOnRestore()=0;
    virtual void VOnLostDevice()=0;
    virtual void VOnUpdate(int deltaMilliseconds)=0;

    virtual void VSetHeight(int h)=0;
    virtual int VGetHeight()=0;
    virtual void VSetWidth(int w)=0;
    virtual int VGetWidth()=0;
    virtual void VSetPosition(Point point)=0;
    virtual Point VGetPosition()=0;
    
    virtual ~IControl() { };
};


}

#endif /* IControl_hpp */
