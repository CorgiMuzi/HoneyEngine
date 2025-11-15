#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL.h>

namespace HoneyEngine
{
	struct SurfaceDeleter {
		void operator()(SDL_Surface* surface) const {
			if (surface) {
				SDL_DestroySurface(surface);
			}
		}
	};

	class ResourceManager;

	class Resource {
	public:
		Resource(const Resource&) = delete;
		Resource& operator=(const Resource&) = delete;

	protected:
		std::unique_ptr<SDL_Surface, SurfaceDeleter> m_surface;

	private:
		friend ResourceManager;
		explicit Resource(SDL_Surface* surface) : m_surface(surface) {}

	public:
		SDL_Surface* getSurface() const { return m_surface.get(); }
	};
}