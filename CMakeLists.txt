cmake_minimum_required(VERSION 3.5.1)

project( multiplayer_demo )

# Engine library is built as a static lib
set( ENGINE_NAME myengine )
file( GLOB ENGINE_SOURCE Engine/src/*.cpp )
add_library( ${ENGINE_NAME} ${ENGINE_SOURCE} )
target_include_directories( ${ENGINE_NAME} 
    PUBLIC Engine/include Engine/enet-1.3.13/include 
)
target_link_libraries( ${ENGINE_NAME} 
    SDL2 SDL2_image SDL2_ttf 
)


# Main app executable
set( EXECUTABLE_NAME app )
add_executable( ${EXECUTABLE_NAME} )
file( GLOB APP_SOURCE src/*.cpp )
target_sources( ${EXECUTABLE_NAME}
    PUBLIC ${APP_SOURCE} 
)
target_include_directories( ${EXECUTABLE_NAME} 
    PUBLIC include 
)
target_link_directories(${EXECUTABLE_NAME} 
    PUBLIC Engine/enet-1.3.13
)
target_link_libraries( ${EXECUTABLE_NAME} 
    ${ENGINE_NAME}
    enet
)

# Server executable
set( EXECUTABLE_SERVER server )
add_executable( ${EXECUTABLE_SERVER} )
target_sources( ${EXECUTABLE_SERVER}
    PRIVATE Server/server.cpp
)
target_include_directories( ${EXECUTABLE_SERVER} 
    PRIVATE Engine/enet-1.3.13/include
)
target_link_directories( ${EXECUTABLE_SERVER} 
    PRIVATE Engine/enet-1.3.13
)
target_link_libraries( ${EXECUTABLE_SERVER}
    enet 
)