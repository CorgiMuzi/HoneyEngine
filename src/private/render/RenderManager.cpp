#include "render/RenderManager.h"
#include "components/IRenderableComponent.h"
#include "resource/ResourceManager.h"
#include "resource/Texture.h"

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

	void RenderManager::registerComponent(IRenderableComponent& targetComponent) {
		m_renderComponents.emplace_back(&targetComponent);
	}

	void RenderManager::unregisterComponent(IRenderableComponent& targetComponent) {
		std::erase(m_renderComponents, &targetComponent);
	}

	void RenderManager::renderAll() {
		for (const auto& renderable : m_renderComponents) {
			renderable->render(this);
		}
	}

	void RenderManager::present() {
		SDL_RenderPresent(m_renderer);
	}

	void RenderManager::term() {

	}

	SDL_Texture* RenderManager::getTexture(const std::string& filePath) {
		if (!m_resourceManager) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "'RenderManager' needs 'ResourceManager' to get textures but there isn't one.");
			return nullptr;
		}

		if (auto textureResource = m_resourceManager->load<Texture>(filePath)) {
			return textureResource->getTexture();
		}

		return nullptr;
	}
}