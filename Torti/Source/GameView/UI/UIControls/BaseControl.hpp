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
    int height;
    int width;
    Point position;
    
    BaseControl(int height, int width, Point position)
        : width(width),
          height(height),
          position(position)
    { }
    
public:
    
    virtual void VOnUpdate(int deltaMilliseconds) override { }
    
    virtual void VSetHeight(int h) override { height = h; }
    virtual int VGetHeight() override { return height; }
    virtual void VSetWidth(int w) override { width = w; }
    virtual int VGetWidth() override { return width; }
    virtual void VSetPosition(Point point) override { position = point; }
    virtual Point VGetPosition() override { return position; }
};

}

#endif /* BaseControl_hpp */
