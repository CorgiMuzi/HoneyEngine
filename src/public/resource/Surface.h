#pragma once

#include "Resource.h"
#include <SDL3/SDL_surface.h>
#include <memory>

namespace HoneyEngine {
    struct SurfaceDeleter {
        void operator()(SDL_Surface* surface) const {
            if (surface) {
                SDL_DestroySurface(surface);
            }
        }
    };

    /**
     * @brief Represents a 2D surface of pixels, typically used for images.
     * This class encapsulates an `SDL_Surface`, which is a CPU-side representation
     * of an image. It holds pixel data in system memory and can be used for
     * software rendering, pixel manipulation, or as an intermediate step before
     * creating GPU textures.
     */
    class Surface final : public Resource {
        friend ResourceManager;
    public:
        explicit Surface(const std::string& filePath) : Resource(filePath) {}
        ~Surface() override = default;

        Surface(const Surface&) = delete;
        Surface& operator=(const Surface&) = delete;

    private:
        std::unique_ptr<SDL_Surface, SurfaceDeleter> m_surface;

    public:
        SDL_Surface* getSurface() const { return m_surface.get(); }

        void setSurface(SDL_Surface* surface) {
            m_surface.reset(surface);
        }
    };
}