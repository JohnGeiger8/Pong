//
//  Margins.hpp
//  Pong
//
//  Created by John Geiger on 7/9/22.
//
#pragma once

#ifndef Margins_hpp
#define Margins_hpp

namespace Torti {

class Margins
{
public:
    int top, bottom, left, right;
    
    Margins(int t, int b, int l, int r)
        : top(t),
          bottom(b),
          left(l),
          right(r)
    { }
    
    static Margins NoMargins;
    
    int GetTotalXMargins();
    int GetTotalYMargins();
};

inline int Margins::GetTotalXMargins()
{
    return right + left;
}

inline int Margins::GetTotalYMargins()
{
    return top + bottom;
}

}
#endif /* Margins_hpp */
