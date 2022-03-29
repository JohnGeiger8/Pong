//
//  InputHandlers.hpp
//  Pong
//
//  Created by John Geiger on 3/27/22.
//
#pragma once

#ifndef InputHandlers_hpp
#define InputHandlers_hpp

#include <string>
#include "Math.hpp"

namespace Torti {

class IKeyboardHandler
{
public:
    virtual bool VOnKeyDown(const uint8_t c)=0;
    virtual bool VOnKeyUp(const uint8_t c)=0;
};

class IPointerHandler
{
public:
    virtual bool VOnPointerMove(const Point &position, const int radius) = 0;
    virtual bool VOnPointerButtonDown(const Point &position, const int radius, const std::string &buttonName) = 0;
    virtual bool VOnPointerButtonUp(const Point &position, const int radius, const std::string &buttonName) = 0;
};

}

#endif /* InputHandlers_hpp */
