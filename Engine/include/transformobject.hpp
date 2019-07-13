#ifndef TRANSFORM_OBJECT_H
#define TRANSFORM_OBJECT_H

#include <gameobject.hpp>

class TransformObject : public GameObject {
    protected:
    public:
        Vector2     position;
        float       rotation;
        
        TransformObject( uint8_t _obj_type );
        ~TransformObject();
        
        void        setPosition( const Vector2& new_val ){position=new_val;};
        Vector2     getPosition() const final {return position;};
        void        setRotation( const float& new_val ){rotation=new_val;}
        float       getRotation() const final {return rotation;};
        Vector2     getGlobalPosition() const ;
        float       getGlobalRotation() const ;
        void        setGlobalPosition(const Vector2& val);
};


#endif