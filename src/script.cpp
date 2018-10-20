#include <engine.hpp>

#include "ship.hpp"
#include "space_scenario.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void InitialScene::init(){
    SpaceScenario* scene = new SpaceScenario(); 
    SpriteObject* bg = new SpriteObject("galaxy_bg.png");
    bg->setZindex( - 10 );
    addChild( scene );
    addChild( bg );

}
