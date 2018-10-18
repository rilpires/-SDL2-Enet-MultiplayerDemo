#ifndef TRANSFORM_OBJECT_H
#define TRANSFORM_OBJECT_H

#include "gameobject.hpp"

class TransformObject : public GameObject {
    protected:
        Vector2     position;
        float       rotation;
    public:
        TransformObject( uint8_t _obj_type );
        void        setPosition( const Vector2& new_val ){position=new_val;};
        Vector2     getPosition() const{return position;};
        void        setRotation( const float& new_val ){rotation=new_val;}
        float       getRotation() const{return rotation;};
        Vector2     getGlobalPosition() const ;
        float       getGlobalRotation() const ;
};


#endif