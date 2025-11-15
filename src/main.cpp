#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/EngineBase.h"

using namespace HoneyEngine;

int main(int argc, char* argv[]) {
    int w_width = 1600;
    int w_height = 900;

    EngineBase::getInstance().initEngine(w_width, w_height);
    EngineBase::getInstance().runEngine();

    return 0;
}