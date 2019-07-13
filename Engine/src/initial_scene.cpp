#include <initial_scene.hpp>

InitialScene::InitialScene( Renderer* rend , PhysicServer* server ):GameObject(GAMEOBJECT_TYPE_INITIAL_SCENE)
{
    physic_server = server;
    renderer = rend;
    name = "InitialScene";
}

void  InitialScene::_frameUpdate(){
    using namespace std;
    
    map< int , vector < SpriteObject* > >	render_object_list;
    vector < PhysicObject*>					physic_object_list;
	vector < GameObject*>					to_delete_list;
    
    
	recursiveSearch( this , &render_object_list , &physic_object_list , &to_delete_list );
	//Deleting every queued to delete
	for ( auto it = to_delete_list.begin(); it != to_delete_list.end() ; ) {
		GameObject* obj = *it;
		delete obj;
		it = to_delete_list.erase(it);
	}
	// Render & Physic server call
    physic_server->updateEverything( physic_object_list );
    renderer->drawEverything( render_object_list );
}



void   InitialScene::recursiveSearch(	GameObject* root , 
										std::map< int , std::vector < SpriteObject* > >* render_object_list , 
										std::vector < PhysicObject*>* physic_object_list ,
										std::vector < GameObject*>* to_delete_list )
{
    for ( auto it = root->getChildren().begin() ; it != root->getChildren().end() ; it ++ ){
		if( (*it)->isQueuedToDelete() ) {
			to_delete_list->push_back( *it );
		}
		else {
			recursiveSearch(*it, render_object_list, physic_object_list , to_delete_list );
			if ((*it)->getObjectType() == GAMEOBJECT_TYPE_RENDER) {
				(*render_object_list)[((SpriteObject*)(*it))->getZindex()].push_back((SpriteObject*)(*it));
			} else
			if ((*it)->getObjectType() == GAMEOBJECT_TYPE_PHYSIC) {
				(*physic_object_list).push_back((PhysicObject*)(*it));
			}
		}
    }
}