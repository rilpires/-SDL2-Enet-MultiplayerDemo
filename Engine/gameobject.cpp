#include "gameobject.hpp"

int GameObject::open_id = 0;

GameObject::GameObject( uint8_t _obj_type ){
    obj_type = _obj_type;
    id = open_id++;
    children = std::vector<GameObject*>(0);
    parent = NULL;
    name = "";
}

void GameObject::addChild( GameObject* obj ){
    if(obj != NULL && obj->getParent() == NULL ){
        children.push_back( obj );
        obj->parent = this;
        if( isInsideTree() ){
            obj->enteredTree();
        }
        else{
            obj->exitedTree();
        }
        
    }
}

void GameObject::removeChild( GameObject* child ){
    for( auto it = children.begin() ; it != children.end() ; it ++ ){
        if( (*it) == child ){
            children.erase( it );
            break;
        }
    }
}

GameObject* GameObject::getChild( std::string child_name ){
    for( auto it = children.begin() ; it != children.end() ; it ++ ){
        if( (*it)->getName() == child_name )
            return *it;
    }
    return NULL;
}

GameObject* GameObject::getChild( int child_id ){
    for( auto it = children.begin() ; it != children.end() ; it ++ ){
        if( (*it)->getId() == child_id )
            return *it;
    }
    return NULL;
}


