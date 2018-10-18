#include "initial_scene.hpp"

InitialScene::InitialScene( Renderer* rend , PhysicServer* server ):GameObject(GAMEOBJECT_TYPE_INITIAL_SCENE)
{
    physic_server = server;
    renderer = rend;
}

void  InitialScene::frameUpdate(){
    using namespace std;
    
    
    map< int , vector < SpriteObject* > > render_object_list;
    vector < PhysicObject*> physic_object_list;
    

    recursiveSearch( this , &render_object_list , &physic_object_list );
    renderer->drawEverything( render_object_list );
    physic_server->updateEverything( physic_object_list );
}



void   InitialScene::recursiveSearch( GameObject* root , std::map< int , std::vector < SpriteObject* > >* render_object_list , std::vector < PhysicObject*>* physic_object_list )
{
    for ( auto it = root->getChildren().begin() ; it != root->getChildren().end() ; it ++ ){
        if( (*it)->getObjectType() == GAMEOBJECT_TYPE_RENDER ){
            (*render_object_list)[ ((SpriteObject*)(*it))->getZindex() ].push_back( (SpriteObject*)(*it) );
        } else
        if( (*it)->getObjectType() == GAMEOBJECT_TYPE_PHYSIC ){
            (*physic_object_list).push_back( (PhysicObject*)(*it) );
        }
        recursiveSearch( *it , render_object_list , physic_object_list );
    }
}