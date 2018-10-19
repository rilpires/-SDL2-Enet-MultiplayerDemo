#ifndef INITIAL_SCENE_H
#define INITIAL_SCENE_H

#include <engine.hpp>

class InitialScene : public GameObject {
    private:
        Renderer*       renderer;
        PhysicServer*   physic_server;
        void            recursiveSearch( GameObject* root , std::map< int , std::vector < SpriteObject* > >* render_object_list , std::vector < PhysicObject*>* physic_object_list );
    public:
        InitialScene( Renderer* rend , PhysicServer* serv );
        void                                                init();
        void                                                _frameUpdate();
        Renderer*                                           getRenderer() const { return renderer ; };
        PhysicServer*                                       getPhysicServer() const { return physic_server ; };
};

#endif