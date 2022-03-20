//
//  Math.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef Math_hpp
#define Math_hpp

namespace Torti {

// FIXME: implement these
class Point
{
public:
    float x = 0.0;
    float y = 0.0;
    
    Point(float x, float y)
      : x(x), y(y) { }
};

class Rect
{
public:
    float bottom, top, right, left;
    
    Rect(float bottom, float top, float right, float left)
        : bottom(bottom),
            top(top),
            right(right),
            left(left)
    { }
};

};

#endif /* Math_hpp */
