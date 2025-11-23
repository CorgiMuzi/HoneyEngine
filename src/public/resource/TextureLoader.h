#pragma once
#include "IResourceLoader.h"
#include "resource/Texture.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

namespace HoneyEngine {
    class TextureLoader final : public IResourceLoader {
    public:
        explicit TextureLoader(SDL_Renderer* renderer) : m_renderer(renderer) {}

        std::shared_ptr<Resource> load(const std::string& filePath) override {
            SDL_Texture* rawTexture = IMG_LoadTexture(m_renderer, filePath.c_str());
            if (!rawTexture) {
                SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to load texture from %s.", filePath.c_str());
                return nullptr;
            }

            auto texture = std::make_shared<Texture>(filePath);
            texture->setTexture(rawTexture);
            return texture;
        }

    private:
        SDL_Renderer* m_renderer;
    };
}
