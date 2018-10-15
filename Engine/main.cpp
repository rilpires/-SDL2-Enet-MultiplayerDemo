#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <engine.h>

Uint32 main_timer_tick( Uint32 interval , void* param );
void main_loop( GameObject* root_game_object );
void frameUpdateRecursive( GameObject* root );
int main( int argc , char** argv ){
    using namespace std;
    if( SDL_Init(SDL_INIT_EVERYTHING) ){
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
    }
    if( ! _init_sdl_params() ){
        std::cout << "Failed: _init_sdl_params()" << std::endl;
    }
    Uint32 IMG_INIT_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG;
    if( IMG_Init( IMG_INIT_FLAGS ) & IMG_INIT_FLAGS != IMG_INIT_FLAGS ){
        std::cout << "Failed: IMG_Init()" << std::endl;
    }
    if( TTF_Init() != 0 ){
        std::cout << "Failed: TTF_Init()" << std::endl;
    }
	enet_initialize();

    InitialScene* initial_object = new InitialScene();
    PhysicServer* physic_server = new PhysicServer();
    PhysicServer::setCurrentPhysicServer( physic_server );
    initial_object->init();
    SDL_AddTimer( 1000.0 / 59.0 , main_timer_tick , NULL );
    SDL_Event sdl_event;
    while(!sdl_quit){
        while( SDL_PollEvent(&sdl_event) > 0 ){
            switch( sdl_event.type ){
                case SDL_USEREVENT:
                    /* Main loop event */
                    if( sdl_event.user.code == 0 ){
                        main_loop( initial_object );
                    }
                    break;
                case SDL_KEYDOWN:
                    Input::receiveEvent( sdl_event );
                    break;
                case SDL_KEYUP:
                    Input::receiveEvent( sdl_event );
                    break;
                case SDL_QUIT:
                    sdl_quit = true;
                    break;
                default:
                    break;
            }
        }
    }
    
    SDL_Quit();

    return 0;
}



Uint32 main_timer_tick( Uint32 interval , void* param ){
    SDL_Event event;
    
    event.type = SDL_USEREVENT;
    event.user.code = 0;
    event.user.data1 = NULL;
    event.user.data2 = NULL;
    SDL_PushEvent( &event );
    
    return interval;
}

void frameUpdateRecursive( GameObject* root ){
    root->frameUpdate();
    std::vector<GameObject*> children = root->getChildren();
    for( auto it = children.begin() ; it != children.end() ; it++ ){
        frameUpdateRecursive( *it );
    }
}

void main_loop( GameObject* initial_object  ){
    using namespace std;
    PhysicServer::getCurrentPhysicServer()->updatePhysics();
    frameUpdateRecursive( initial_object );
    Renderer::drawEverything();
    Input::updateKeys();
}




