#include <engine.h>

#include "ship.h"
#include "space_scenario.h"

void InitialScene::init(){
    SpaceScenario* scene = new SpaceScenario(); 
    addChild( scene );
}
