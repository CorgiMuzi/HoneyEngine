#pragma once

#include "resource/Texture.h"

namespace HoneyEngine {
    class RenderManager;

    class Sprite {
    public:
        explicit Sprite(std::shared_ptr<Texture> texture);
        Sprite(std::shared_ptr<Texture> texture, const float x, const float y, const float w, const float h) : m_texture(std::move(texture)), m_srcRect{x, y, w, h} {}

        void render(RenderManager* renderManager);

    private:
        std::string m_name{""};
        std::shared_ptr<Texture> m_texture;
        SDL_FRect m_srcRect{0, 0, 0, 0};

    public:
        SDL_Texture* getTexture() const { return m_texture ? m_texture->getTexture() : nullptr; }
        SDL_FRect getSrcRect() const { return m_srcRect;}
        float getWidth() const { return m_srcRect.w; }
        float getHeight() const {return m_srcRect.h; }
    };
}