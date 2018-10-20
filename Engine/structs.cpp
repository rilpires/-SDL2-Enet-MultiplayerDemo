#include "structs.hpp"

void _print( const std::string& a ){ std::cout << a << std::endl ; }

Vector2 Vector2::normalized(){
    float length = this->length();
    if( length < 0.00001 ) 
        return Vector2(0,0);
    else
        return Vector2( x / length , y / length );
}


std::ostream& operator<< ( std::ostream& os , const Vector2& v ){
    os << "(" << v.x << " , " << v.y << ")" << std::endl;
    return os;
}


bool    Rect2::collidesWith( const Rect2& other_rect ){
    if( x + w < other_rect.x ){
        return false;    
    } else
    if( x > other_rect.x + other_rect.w ){
        return false;
    } else
    if( y + h < other_rect.y ){
        return false;    
    } else
    if( y > other_rect.y + other_rect.h ){
        return false;
    } else
        return true;
}




