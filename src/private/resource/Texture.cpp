#include "resource/Texture.h"
namespace HoneyEngine {
    void Texture::setTexture(SDL_Texture* texture) {
        m_texture.reset(texture);

        if (m_texture) {
            float w, h;
            SDL_GetTextureSize(m_texture.get(), &w, &h);
            m_textureSize = {w, h};
        }else {
            m_textureSize = {0.f, 0.f};
        }
    }
}
