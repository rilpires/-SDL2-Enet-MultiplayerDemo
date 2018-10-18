#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <engine.hpp>

Uint32 main_timer_tick( Uint32 interval , void* param );
void main_loop( GameObject* root_game_object );
void frameUpdateRecursive( GameObject* root );
int main( int argc , char** argv ){
    using namespace std;
    if( SDL_Init(SDL_INIT_EVERYTHING) ){
        std::cout << "SDL error: " << SDL_GetError() << std::endl;
    }
    Uint32 IMG_INIT_FLAGS = IMG_INIT_PNG | IMG_INIT_JPG;
    if( IMG_Init( IMG_INIT_FLAGS ) & IMG_INIT_FLAGS != IMG_INIT_FLAGS ){
        std::cout << "Failed: IMG_Init()" << std::endl;
    }
    if( TTF_Init() != 0 ){
        std::cout << "Failed: TTF_Init()" << std::endl;
    }
    /* Initializing renderer */
    SDL_Window* sdl_window = SDL_CreateWindow("SpaceShooterVS" , 300 , 50 , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN );    
    SDL_Renderer* sdl_renderer = SDL_CreateRenderer( sdl_window , -1 , SDL_RENDERER_ACCELERATED  );
    Renderer* renderer = new Renderer( sdl_window , sdl_renderer );

    /* Initializing physic server */
    PhysicServer* physic_server = new PhysicServer();
    
    /* Initializing root object */
    InitialScene* initial_object = new InitialScene( renderer , physic_server );
    
    /* Load all resourcers with renderer */
    renderer->loadTexture( "player_ship.png" );
    renderer->loadTexture( "other_player_ship.png" );

    initial_object->init();
    SDL_AddTimer( 1000.0 / 50.0 , main_timer_tick , NULL );
    SDL_Event sdl_event;
    bool QUIT = false;
    while(!QUIT){
        while( SDL_PollEvent(&sdl_event) > 0 ){
            switch( sdl_event.type ){
                case SDL_USEREVENT:
                    /*<============ Main loop event ==============>*/
                    if( sdl_event.user.code == 0 ){
                        frameUpdateRecursive( initial_object );
                        Input::updateKeys();
                    }
                    break;
                case SDL_KEYDOWN:
                    Input::receiveEvent( sdl_event );
                    break;
                case SDL_KEYUP:
                    Input::receiveEvent( sdl_event );
                    break;
                case SDL_QUIT:
                    QUIT = true;
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






