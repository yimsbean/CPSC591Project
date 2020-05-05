#include "World.h"

namespace Engine{

void 
World::loadScene(int sceneNo){
    reset();
    switch(sceneNo){
        case 1:
            scene1(); break;
        //case 2:
        //    scene2(); break;
    }
    draw();
}

void
World::scene1(){
	readFromSceneFile("resources/scenes/scene1.json");
    currentScene = 1;
}
void
World::scene2(){
    //readFromSceneFile("resources/scenes/scene2.json");
    //currentScene = 2;
}

}