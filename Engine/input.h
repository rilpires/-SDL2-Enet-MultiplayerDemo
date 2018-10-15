#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>

class Input{

    struct Key{
        bool pressed = false;
        bool pressed_down = false;
        bool pressed_up = false;
    };

    private:
        static std::map<Sint32,Key> keys;
    public:
        static void init( );
        static void receiveEvent( SDL_Event event );
        static bool isKeyPressed( SDL_Keycode scancode);
        static void updateKeys();
};

#endif