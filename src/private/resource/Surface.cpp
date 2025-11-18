#include "resource/Surface.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace HoneyEngine {
    bool Surface::load() {
        SDL_Surface* newSurface = IMG_Load(getFilePath().c_str());
        if (!newSurface) {
            std::cerr << "Error: Failed to load the surface from : " << getFilePath() << "\nSDL_image Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_surface.reset(newSurface);
        return true;
    }
}