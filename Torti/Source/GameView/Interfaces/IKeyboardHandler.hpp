//
//  IKeyboardHandler.hpp
//  Pong
//
//  Created by John Geiger on 7/5/22.
//
#pragma once

#ifndef IKeyboardHandler_hpp
#define IKeyboardHandler_hpp

namespace Torti {

class IKeyboardHandler
{
public:
    virtual bool VOnKeyDown(const int key)=0;
    virtual bool VOnKeyUp(const int key)=0;
};

}

#endif /* IKeyboardHandler_hpp */
