//
//  IPointerHandler.hpp
//  Pong
//
//  Created by John Geiger on 7/5/22.
//

#ifndef IPointerHandler_hpp
#define IPointerHandler_hpp

#include <string>
#include "Math.hpp"

namespace Torti {

class IPointerHandler
{
public:
    virtual bool VOnPointerMove(const Point &position, const int radius) = 0;
    virtual bool VOnPointerButtonDown(const Point &position, const int radius, const std::string &buttonName) = 0;
    virtual bool VOnPointerButtonUp(const Point &position, const int radius, const std::string &buttonName) = 0;
};

}

#endif /* IPointerHandler_hpp */
