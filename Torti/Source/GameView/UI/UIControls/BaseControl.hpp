//
//  BaseControl.hpp
//  Pong
//
//  Created by John Geiger on 7/8/22.
//
#pragma once

#ifndef BaseControl_hpp
#define BaseControl_hpp

#include "IControl.hpp"

namespace Torti {

///
/// Base class for many UI Controls
///
class BaseControl : public IControl
{
protected:
    int mHeight;
    int mWidth;
    Point mPosition;
    
    BaseControl(int height, int width, Point position)
        : mWidth(width),
          mHeight(height),
          mPosition(position)
    { }
    
public:
    
    virtual void VOnUpdate(int deltaMilliseconds) override { }
    
    virtual void VSetHeight(int h) override { mHeight = h; }
    virtual int VGetHeight() override { return mHeight; }
    virtual void VSetWidth(int w) override { mWidth = w; }
    virtual int VGetWidth() override { return mWidth; }
    virtual void VSetPosition(Point point) override { mPosition = point; }
    virtual Point VGetPosition() override { return mPosition; }
};

}

#endif /* BaseControl_hpp */
