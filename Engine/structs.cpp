#include "structs.h"

Vector2::Vector2(){
    x = 0;
    y = 0;
}

Vector2::Vector2( float _x , float _y ){
    x = _x;
    y = _y;
}

void Vector2::operator= (const Vector2& v){
    x = v.x;
    y = v.y;
}
Vector2 Vector2::operator+ (const Vector2& v){
    return Vector2( x + v.x , y + v.y );
}
Vector2 Vector2::operator* (const Vector2& v){
    return Vector2( x * v.x , y * v.y );
}
Vector2 Vector2::operator* (const float& f){
    return Vector2( x * f , y * f );
}
Vector2& Vector2::operator+= (const Vector2& v){
    x += v.x;
    y += v.y;
    return *this;
}

Vector2 Vector2::rotatedByRad( const float& rad ){
    float current_rad = atan2( y , x );
    float new_rad = current_rad + rad;
    float length = this->length();
    return Vector2( length * cos( new_rad ) , length * sin( new_rad ) );
}
Vector2 Vector2::normalized(){
    float length = this->length();
    if( length < 0.00001 ) 
        return Vector2(0,0);
    else
        return Vector2( x / length , y / length );
}
float Vector2::angle() const {
    return atan2( y , x );
}
float Vector2::length() const {
    return pow( pow( x , 2 ) + pow( y , 2 ) , 0.5 );
}



Rect2::Rect2(){
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}

Rect2::Rect2( Vector2 pos , Vector2 size ){
    x = pos.x;
    y = pos.y;
    w = size.x;
    h = size.y;
}

Rect2::Rect2( float _x , float _y , float _w , float _h ){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}



std::ostream& operator<< ( std::ostream& os , const Vector2& v ){
    os << "(" << v.x << " , " << v.y << ")" << std::endl;
    return os;
}








