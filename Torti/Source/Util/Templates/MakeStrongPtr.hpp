//
//  MakeStrongPtr.hpp
//  Pong
//
//  Created by John Geiger on 6/15/22.
//

#ifndef MakeStrongPtr_hpp
#define MakeStrongPtr_hpp

#include <memory>

namespace Torti {

///
/// Convert weak ptr to strong pointer and return; if expired, return new shared ptr
///
template <class Type>
std::shared_ptr<Type> MakeStrongPtr(std::weak_ptr<Type> pWeakPtr)
{
    if (!pWeakPtr.expired())
        return std::shared_ptr<Type>(pWeakPtr);
    else
        return std::shared_ptr<Type>();
}

}

#endif /* MakeStrongPtr_hpp */
