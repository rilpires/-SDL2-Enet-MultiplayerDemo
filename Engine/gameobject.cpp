#include "gameobject.h"

int GameObject::open_id = 0;

GameObject::GameObject(){
    id = open_id++;
    children = std::vector<GameObject*>(0);
    parent = NULL;
    name = "";
    inside_tree = false;
}

void GameObject::setInsideTree(bool val){
    using namespace std;

    inside_tree = val;
    for( auto it = children.begin() ; it != children.end() ; it++ ){
        (*it)->setInsideTree(val);
    }
}


bool   GameObject::isInsideTree(){
    return inside_tree;
}

void   GameObject::exitTree(){
    using namespace std;
    if( ! inside_tree ) return;

    if( parent != NULL ){
        parent->removeChild( this );
    }
    setInsideTree(false);
}

void GameObject::addChild( GameObject* obj ){
    if(obj != NULL && obj->getParent() == NULL ){
        children.push_back( obj );
        
        if( isInsideTree() ){
            obj->setInsideTree( true );
            obj->enteredTree();
        }
        else{
            obj->setInsideTree( false );
            obj->exitedTree();
        }
        
    }
}

void GameObject::removeChild( GameObject* child ){
    for( auto it = children.begin() ; it != children.end() ; it ++ ){
        if( (*it) == child ){
            child->exitTree();
            children.erase( it );
            break;
        }
    }
}

GameObject* GameObject::getParent(){
    return parent;
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

int GameObject::getId(){
    return id;
}

std::string GameObject::getName(){
    return name;
}

void GameObject::setName( std::string name_ ){
    name = name_;
}

Vector2  GameObject::getPosition(){
    return Vector2(0,0);
}

std::vector<GameObject*>& GameObject::getChildren(){
    return children;
}


