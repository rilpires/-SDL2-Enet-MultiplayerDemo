#include "transformobject.hpp"

TransformObject::TransformObject(uint8_t _obj_type) : GameObject(_obj_type) {
    position = Vector2(0,0);
    rotation = 0;
}


Vector2     TransformObject::getGlobalPosition() const {
    Vector2 ret = getPosition();
    GameObject* parent = getParent();
    while( parent != NULL ){
        ret += parent->getPosition();
        parent = parent->getParent();
    }
    return ret;
}
float     TransformObject::getGlobalRotation() const {
    float ret = getRotation();
    GameObject* parent = getParent();
    while( parent != NULL ){
        ret += parent->getRotation();
        parent = parent->getParent();
    }
    return ret;
}

void        TransformObject::setGlobalPosition(const Vector2& val){
    Vector2 current_global_position = getGlobalPosition();
    setPosition( getPosition() + val - current_global_position  );
}

