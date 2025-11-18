#include "render/RenderManager.h"
#include "resource/Surface.h"
#include "resource/ResourceManager.h"

#include <SDL3/SDL.h>

namespace HoneyEngine
{
	RenderManager::RenderManager(SDL_Renderer* renderer, ResourceManager* resourceManager) : m_renderer(renderer), m_resourceManager(resourceManager) {
	}

	RenderManager::~RenderManager() {
	}

	void RenderManager::clearScreen() {
		clearScreen(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	}

	void RenderManager::clearScreen(const SDL_Color& color) {
		clearScreen(color.r, color.g, color.b, color.a);
	}

	void RenderManager::clearScreen(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
		SDL_RenderClear(m_renderer);
	}

	void RenderManager::present() {
		SDL_RenderPresent(m_renderer);
	}

	void RenderManager::draw(const std::string& filePath, int x, int y) {
		SDL_Texture* texture = getTexture(filePath);
		if (!texture) return;

		SDL_FRect destRect{ static_cast<float>(x), static_cast<float>(y), 0.f, 0.f };
		SDL_PropertiesID props = SDL_GetTextureProperties(texture);
		destRect.w = SDL_GetFloatProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0.f);
		destRect.h = SDL_GetFloatProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0.f);

		SDL_RenderTexture(m_renderer, texture, nullptr, &destRect);
	}

	void RenderManager::term() {
		m_textureCache.clear();
	}

	SDL_Texture* RenderManager::getTexture(const std::string& filePath) {
		if (auto it = m_textureCache.find(filePath); it != m_textureCache.end()) return it->second.get();

		return createTexture(filePath);
	}

	SDL_Texture* RenderManager::createTexture(const std::string& filePath) {
		if (!m_resourceManager) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ERROR: Resource manager is not set.");
			return nullptr;
		}

		auto resource = m_resourceManager->load<Surface>(filePath);
		if (!resource || !resource->getSurface()) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load surface from path: %s", filePath.c_str());
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, resource->getSurface());
		if (!texture) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from path: %s", filePath.c_str());
			return nullptr;
		}

		auto [it, isInserted] = m_textureCache.emplace(filePath, std::unique_ptr<SDL_Texture, TextureDeleter>(texture));
		if (isInserted) {
			return it->second.get();
		}
		else {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to insert texture into cache for path: %s", filePath.c_str());
			SDL_DestroyTexture(texture);
			return nullptr;
		}
	}
}