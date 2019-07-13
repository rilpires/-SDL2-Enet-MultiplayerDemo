#include <path_finder.hpp>
#include <cstring>
#include <SDL2/SDL.h>

#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif

std::string getResDirPath(){

    using namespace std;




    string str = string( SDL_GetBasePath() ) + string("resources") + PATH_SEP;
    return str;

}

std::string getResPath( const char* resource_name ){
    return getResDirPath() + std::string(resource_name) ;
}

