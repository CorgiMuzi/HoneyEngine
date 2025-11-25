#pragma once

#include "resource/Resource.h"
#include <memory>
#include <glm/glm.hpp>
#include <SDL3/SDL_render.h>

namespace HoneyEngine {
    struct TextureDeleter {
        /**
         * @brief Custom deleter for SDL_Texture.
         * This functor is used with std::unique_ptr to ensure that SDL_DestroyTexture is called when the unique_ptr goes out of scope.
         */
        void operator()(SDL_Texture* texture) const {
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
    };

    /**
     * @brief
     */
    class Texture final : public Resource {
    public:
        explicit Texture(const std::string& filePath) : Resource(filePath) {}
        ~Texture() override = default;

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

    private:
        std::string m_name{""};
        std::unique_ptr<SDL_Texture, TextureDeleter> m_texture;
        glm::vec2 m_textureSize{0.f,0.f };

    public:
        std::string getName() const {return m_name;}
        SDL_Texture* getTexture() const { return m_texture.get();}
        glm::vec2 getTextureSize() const { return m_textureSize; }

        void setTexture(SDL_Texture* texture);
    };
}
