#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include "structs.h"   

class GameObject {
    private:
        static int      open_id;
        bool            inside_tree;
    protected:
        int                         id;
        std::string                 name;
        GameObject*                 parent;
        std::vector<GameObject*>    children;
        void                        setInsideTree(bool val);
    public:
        GameObject();
        
        int                         getId();
        std::string                 getName();
        void                        setName( std::string _name );
        void                        addChild( GameObject* child );
        void                        removeChild( GameObject* child );
        GameObject*                 getParent();
        GameObject*                 getChild( std::string child_name );
        GameObject*                 getChild( int child_id );
        std::vector<GameObject*>&   getChildren();
        bool                        isInsideTree();
        void                        exitTree();


        virtual Vector2 getPosition();

        virtual void    frameUpdate(){};
        virtual void    enteredTree(){};
        virtual void    exitedTree(){};
         
};

#endif