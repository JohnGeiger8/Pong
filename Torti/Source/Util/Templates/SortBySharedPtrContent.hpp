//
//  SortBySharedPtrContent.hpp
//  Pong
//
//  Created by John Geiger on 6/26/22.
//
#pragma once

#ifndef SortBySharedPtrContent_hpp
#define SortBySharedPtrContent_hpp

#include <memory>

namespace Torti {

template<class T>
struct SortBy_SharedPtr_Content
{
    bool operator()(const std::shared_ptr<T> &lhs, const std::shared_ptr<T> &rhs) const
        { return *lhs < *rhs; }
};

}

#endif /* SortBySharedPtrContent_hpp */
