#ifndef STRUCTS_H
#define STRUCTS_H

#include <math.h>
#include <iostream>

using namespace std;

struct Vector2{
    float x;
    float y;
    Vector2();
    Vector2( float _x , float _y );
    void operator= (const Vector2& v);
    Vector2 operator+ (const Vector2& v);
    Vector2 operator- (const Vector2& v);
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
    bool    collidesWith( const Rect2& other_rect );
};

// Vector2 INLINES ============>
inline Vector2::Vector2(){
    x = 0;
    y = 0;
}
inline Vector2::Vector2( float _x , float _y ){
    x = _x;
    y = _y;
}
inline void Vector2::operator= (const Vector2& v){
    x = v.x;
    y = v.y;
}
inline Vector2 Vector2::operator+ (const Vector2& v){
    return Vector2( x + v.x , y + v.y );
}
inline Vector2 Vector2::operator- (const Vector2& v){
    return Vector2( x - v.x , y - v.y );
}
inline Vector2 Vector2::operator* (const Vector2& v){
    return Vector2( x * v.x , y * v.y );
}
inline Vector2 Vector2::operator* (const float& f){
    return Vector2( x * f , y * f );
}
inline Vector2& Vector2::operator+= (const Vector2& v){
    x += v.x;
    y += v.y;
    return *this;
}
inline Vector2 Vector2::rotatedByRad( const float& rad ){
    float current_rad = atan2( y , x );
    float new_rad = current_rad + rad;
    float length = this->length();
    return Vector2( length * cos( new_rad ) , length * sin( new_rad ) );
}
inline float Vector2::angle() const {
    return atan2( y , x );
}
inline float Vector2::length() const {
    return pow( pow( x , 2 ) + pow( y , 2 ) , 0.5 );
}


// Rect2 INLINES ============>
inline Rect2::Rect2(){
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}
inline Rect2::Rect2( Vector2 pos , Vector2 size ){
    x = pos.x;
    y = pos.y;
    w = size.x;
    h = size.y;
}
inline Rect2::Rect2( float _x , float _y , float _w , float _h ){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}





#include <ostream>
std::ostream& operator<< ( std::ostream& os , const Vector2& v );

#endif