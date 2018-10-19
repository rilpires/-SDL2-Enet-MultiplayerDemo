#include "gameobject.hpp"
#include "physic_object.hpp"

int GameObject::open_id = 0;

GameObject::GameObject( uint8_t _obj_type ){
    obj_type = _obj_type;
    id = open_id++;
    children = std::vector<GameObject*>(0);
    parent = NULL;
	to_delete = false;
    name = "";
}
GameObject::~GameObject(){
	if (!to_delete)
		cout << "You should'nt call delete on gameobjects!!!! use queueDelete() instead " << endl;
	if (getParent() != NULL) {
		getParent()->removeChild(this);
	}
    for( auto it = children.begin() ; it != children.end() ;){
		GameObject* child = (*it);
		it = children.erase(it);
		delete child;
    }
}
void GameObject::addChild( GameObject* obj ){
    //std::cout<< "("<<getId()<<")"<<name<<" adding as a child: ("<<obj->getId()<<")" << obj->name << std::endl;
    if(obj != NULL && obj->getParent() == NULL ){
        children.push_back( obj );
        obj->parent = this;
        if( isInsideTree() ){
            obj->enteredTree();
        }
    }
}

void GameObject::removeChild( GameObject* child ){
    //std::cout<< "("<<getId()<<")"<<name<<" removing child: ("<<child->getId()<<")" << child->name << std::endl;
    for( auto it = children.begin() ; it != children.end() ; it ++ ){
        if( (*it) == child ){
            child->parent = NULL;
            child->exitedTree();
            it = children.erase( it );
			it--;
            return;
        }
    }
}

GameObject* GameObject::getChild( std::string child_name ){
    for( auto it = children.begin() ; it != children.end() ; it ++ ){
        if( (*it)->name == child_name )
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


void    GameObject::enteredTree(){
}

void GameObject::exitedTree(){
}