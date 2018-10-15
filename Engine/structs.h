#ifndef STRUCTS_H
#define STRUCTS_H

#include <math.h>

struct Vector2{
    float x;
    float y;
    Vector2();
    Vector2( float _x , float _y );
    void operator= (const Vector2& v);
    Vector2 operator+ (const Vector2& v);
    Vector2 operator* (const Vector2& v);
    Vector2 operator* (const float& f);
    Vector2& operator+= (const Vector2& v);
    Vector2 rotatedByRad( const float& rad );
    Vector2 normalized();
    float angle() const;
    float length() const;
};

struct Rect2{
    float x;
    float y;
    float w;
    float h;
    Rect2();
    Rect2( Vector2 pos , Vector2 size );
    Rect2( float _x , float _y , float _w , float _h );
};

#include <ostream>

std::ostream& operator<< ( std::ostream& os , const Vector2& v );

#endif