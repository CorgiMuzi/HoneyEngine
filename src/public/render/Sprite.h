#pragma once

#include "resource/Texture.h"

namespace HoneyEngine {
    class Sprite {
    public:
        explicit Sprite(std::shared_ptr<Texture> texture) : m_texture(std::move(texture)){}
        Sprite(Texture* texture, const int x, const int y, const int w, const int h);

    private:
        std::shared_ptr<Texture> m_texture;
        SDL_FRect srcRect{0, 0, 0, 0};

    public:
        SDL_Texture* getTexture() const { return m_texture ? m_texture->getTexture() : nullptr; }
        SDL_FRect getSrcRect() const { return srcRect;}
    };
}