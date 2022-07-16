//
//  IScreenElement.hpp
//  Pong
//
//  Created by John Geiger on 3/28/22.
//
#pragma once

#ifndef IScreenElement_hpp
#define IScreenElement_hpp

#include "AppMessage.hpp"

namespace Torti {

class IScreenElement
{
public:
    virtual void VOnRender(double fTime, float fElapsedTime) = 0;
    
    ///
    /// Called just after class is instantiated, and when interruption such as change in resolution or being awoken from sleep
    ///
    virtual void VOnRestore() = 0;
    virtual void VOnLostDevice()=0;
    virtual void VOnUpdate(int deltaMilliseconds) = 0;

    virtual int VGetZOrder() const = 0;
    virtual void VSetZOrder(int const zOrder) = 0;
    virtual bool VIsVisible() const = 0;
    virtual void VSetVisible(bool visible) = 0;

    virtual bool VOnAppMessage(AppMessage msg)=0;

    virtual ~IScreenElement() { };
    virtual bool const operator <(IScreenElement const &other) { return VGetZOrder() < other.VGetZOrder(); }
};

///
/// Represents generic UI element with position and size
///
class UIElement : public IScreenElement
{
protected:
    int mPositionX, mPositionY;
    int mWidth, mHeight;
    
    bool m_bIsVisible;
    
public:
    UIElement()
      : mPositionX(0),
        mPositionY(0),
        mWidth(100),
        mHeight(100),
        m_bIsVisible(true)
    { }
    
    virtual int VGetWidth() { return mWidth; };
    virtual int VGetHeight() { return mHeight; };
    virtual int VGetPositionX() { return mPositionX; };
    virtual int VGetPositionY() { return mPositionY; };
    
    virtual void VSetWidth(int width) { mWidth = width; };
    virtual void VSetHeight(int height) { mHeight = height; };
    virtual void VSetPositionX(int x) { mPositionX = x; };
    virtual void VSetPositionY(int y) { mPositionY = y; };
    
    virtual void VOnUpdate(int deltaMilliseconds) override { }
    virtual bool VIsVisible() const override { return m_bIsVisible; }
    virtual void VSetVisible(bool visible) override { m_bIsVisible = visible; }
};

}


#endif /* IScreenElement_hpp */
