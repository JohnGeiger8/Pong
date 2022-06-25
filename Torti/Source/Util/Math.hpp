//
//  Math.hpp
//  Pong
//
//  Created by John Geiger on 3/19/22.
//
#pragma once

#ifndef Math_hpp
#define Math_hpp

#include <stdio.h>

namespace Torti {

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

// FIXME: implement
class Vector
{
public:
    float x = 0.0;
    float y = 0.0;
    
    Vector(float x, float y) : x(x), y(y)
    { }
    
    
//    Vector operator+(Vector& rhs) { }
};

// FIXME: implement
// FIXME: some of the logic behind this is getting a bit dicey... Do i need a 3x3 matrix? Am I overthinking? Think more about actual use case before you implement everything, just leave it as essentially an interface for now.
///
/// 2-dimensional matrix
///
class Mat2x2
{
private:
    float topLeft, topRight, bottomLeft, bottomRight;
    
public:
    static const Mat2x2 gIdentity;
    
    Mat2x2() { *this = Mat2x2::gIdentity; }
    Mat2x2(float tl, float tr, float bl, float br)
        : topLeft(tl),
            topRight(tr),
            bottomLeft(bl),
            bottomRight(br)
    { }
    
    Vector GetPosition() const
        { return { bottomLeft, bottomRight }; }
    void SetPosition(const Vector pos)
        { bottomLeft = pos.x; bottomRight = pos.y; }
    Vector GetDirection() const
        { return { topLeft, topRight }; }
    
public:
    Mat2x2 operator+ (Mat2x2 const &matrix);
    Mat2x2 operator- (Mat2x2 const &matrix);
    Mat2x2 operator* (Mat2x2 const &matrix);
    
    void Scale(const float scalingFactor) { printf("Error: unimplemented function Mat2x2::Scale.\n"); };
    void Translate(const float translation) { printf("Error: unimplemented function Mat2x2::Translate.\n"); };
    
    void BuildRotationY(float angleRadians) { printf("Error: unimplemented function Mat2x2::BuildRotationY.\n"); };
};

};

#endif /* Math_hpp */
