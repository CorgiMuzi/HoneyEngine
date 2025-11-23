#pragma once
#include "IResourceLoader.h"
#include "resource/Surface.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

namespace HoneyEngine {
    class SurfaceLoader final : public IResourceLoader {
    public:
        explicit SurfaceLoader() {}

        std::shared_ptr<Resource> load(const std::string& filePath) override {
            SDL_Surface* rawSurface = IMG_Load(filePath.c_str());
            if (!rawSurface) {
                SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to load surface from %s.", filePath.c_str());
                return nullptr;
            }

            auto surface = std::make_shared<Surface>(filePath);
            surface->setSurface(rawSurface);
            return surface;
        }
    };
}
