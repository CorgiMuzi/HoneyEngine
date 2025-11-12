#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/EngineCore.h"

int main(int argc, char* argv[]) {
    int w_width = 1600;
    int w_height = 900;

    EngineCore::getInstance().initEngine(w_width, w_height);
    EngineCore::getInstance().runEngine();

    return 0;
}