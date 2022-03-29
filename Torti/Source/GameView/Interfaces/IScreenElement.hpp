//
//  IScreenElement.hpp
//  Pong
//
//  Created by John Geiger on 3/28/22.
//
#pragma once

#ifndef IScreenElement_hpp
#define IScreenElement_hpp

namespace Torti {

class IScreenElement
{
public:
    virtual void VOnRender(double fTime, float fElapsedTime) = 0;
    virtual void VOnUpdate(int deltaMilliseconds) = 0;

    virtual int VGetZOrder() const = 0;
    virtual void VSetZOrder(int const zOrder) = 0;
    virtual bool VIsVisible() const = 0;
    virtual void VSetVisible(bool visible) = 0;

//    virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;

    virtual ~IScreenElement() { };
    virtual bool const operator <(IScreenElement const &other) { return VGetZOrder() < other.VGetZOrder(); }
};

}


#endif /* IScreenElement_hpp */
