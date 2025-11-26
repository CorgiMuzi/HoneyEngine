#include "render/Sprite.h"
#include <iostream>
#include <format>

namespace HoneyEngine {
    Sprite::Sprite(std::shared_ptr<Texture> texture) : m_texture(std::move(texture)) {
        if (m_texture) {
            glm::vec2 size = m_texture->getTextureSize();

            m_srcRect = {0.f, 0.f, size.x, size.y};
        }else {
            m_srcRect = {0.f, 0.f, 0.f, 0.f};
        }
    }

    void Sprite::render(RenderManager* renderManager) {
         if (!renderManager) {
             const std::string err = std::format("Sprite '{}': Sprite needs render manager but is missing.", getName());
         }
    }

}