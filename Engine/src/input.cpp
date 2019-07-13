#include <input.hpp>


std::map<Sint32,Input::Key> Input::keys;

/**
Sint32 all_input_keycodes[8] = {
    SDLK_LEFT ,
    SDLK_RIGHT,
    SDLK_UP,
    SDLK_DOWN,
    SDLK_z,
    SDLK_x,
    SDLK_RETURN,
    SDLK_SPACE
};
void Input::init(){
    for( int i = 0 ; i < 8 ; i ++ ){
        Key key;
        key.keycode = all_input_keycodes[i];
        key.pressed = false;
        key.pressed_down = false;
        key.pressed_up = false;
        keys.insert( std::pair<Sint32,Key>( all_input_keycodes[i] , key ) );
    }
}
**/


void Input::receiveEvent( SDL_Event event ){
    if( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ){
        Sint32 keycode = event.key.keysym.scancode;
        keys[keycode].pressed_down = ( event.type == SDL_KEYDOWN ) && !keys[keycode].pressed ;
        keys[keycode].pressed      = ( event.type == SDL_KEYDOWN );
        keys[keycode].pressed_up   = ( event.type == SDL_KEYUP );
    }
}

void Input::updateKeys( ){
    for( auto it = keys.begin() ; it != keys.end() ; it ++ ){
        (it->second).pressed_down = false;
        (it->second).pressed_up   = false;
    }
}


bool Input::isKeyPressed( SDL_Keycode scancode ){
    return keys[scancode].pressed;
}

bool Input::wasKeyPressedDown( SDL_Keycode scancode){
    return keys[scancode].pressed_down;
}
bool Input::wasKeyPressedUp( SDL_Keycode scancode){
    return keys[scancode].pressed_up;
}






