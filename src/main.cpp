#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/EngineBase.h"

// Temporal headers for testing purpose
#include "game/Scene.h"

using namespace HoneyEngine;

int main(int argc, char* argv[]) {
    int w_width = 1600;
    int w_height = 900;

    EngineBase* engine = EngineBase::getInstance();
    engine->initEngine(w_width, w_height);

    engine->loadScene(std::make_unique<Scene>("MainScene"));

    engine->runEngine();



    return 0;
}