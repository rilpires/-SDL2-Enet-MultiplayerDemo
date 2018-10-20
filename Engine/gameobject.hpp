#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "structs.hpp"

enum GAMEOBJECT_TYPE : uint8_t { 
    GAMEOBJECT_TYPE_DEFAULT = 0 , 
    GAMEOBJECT_TYPE_INITIAL_SCENE ,  
    GAMEOBJECT_TYPE_RENDER , 
    GAMEOBJECT_TYPE_PHYSIC };
class GameObject {
    private:
        uint8_t                     obj_type;
        static int                  open_id;
        virtual void                enteredTree();
        virtual void                exitedTree();
		bool						to_delete;
    protected:
        int                         id;
        GameObject*                 parent;
        std::vector<GameObject*>    children;
    public:

        std::string                 name;

        GameObject( uint8_t _obj_type = GAMEOBJECT_TYPE_DEFAULT );
        virtual ~GameObject();
        
        uint8_t                     getObjectType(){return obj_type;}
        int                         getId(){return id;};
        void                        addChild( GameObject* child );
        void                        removeChild( GameObject* child );
        GameObject*                 getParent() const{return parent;};
        GameObject*                 getChild( std::string child_name );
        GameObject*                 getChild( int child_id );
        std::vector<GameObject*>&   getChildren(){return children;}
        bool                        isInsideTree() const ;
		bool						isQueuedToDelete() { return to_delete; }
		void						queueDelete();


        virtual Vector2 getPosition() const{return Vector2(0,0);}
        virtual float   getRotation() const{return 0;}

        virtual void    _frameUpdate(){};
         
};

inline bool                        GameObject::isInsideTree() const{
    if( obj_type == GAMEOBJECT_TYPE_INITIAL_SCENE )
        return true;
    else{
        if( getParent() == NULL )
            return false;
        else
            return getParent()->isInsideTree();   
    }
} 

inline void			GameObject::queueDelete() { 
	to_delete = true; 
	for (auto it = children.begin(); it != children.end(); it++)
		(*it)->queueDelete();
}


#endif