//
//  Color.hpp
//  Pong
//
//  Created by John Geiger on 3/25/22.
//
#pragma once

#ifndef Color_hpp
#define Color_hpp

#include <stdint.h>

namespace Torti {

class Color
{
public:
    uint8_t r, g, b, a;
    
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r(r),
          g(g),
          b(b),
          a(a)
    { }
};

}

#endif /* Color_hpp */
