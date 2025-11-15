#include "components/SpriteRendererComponent.h"
#include "components/TransformComponent.h"
#include "gameplay/GameObject.h"
#include <SDL3/SDL.h>
#include <cassert>

namespace HoneyEngine
{
	SpriteRendererComponent::SpriteRendererComponent(GameObject* owner, SDL_Texture* texture) : IComponent(), m_texture(texture) {
		setOwner(owner);
	}

	void SpriteRendererComponent::init() {
		assert(getOwner()->getComponent<TransformComponent>() &&
			"SpriteRendererComponent requires a TransformComponent, but it was not found on the GameObject.");

		if (m_texture) {
			// Caching texture properties
			SDL_PropertiesID props = SDL_GetTextureProperties(m_texture);
			m_width = SDL_GetFloatProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0.f);
			m_height = SDL_GetFloatProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0.f);
		}
	}

	void SpriteRendererComponent::render(SDL_Renderer* renderer) {
		if (!m_texture || !renderer) return;

		TransformComponent* transform = getOwner()->getComponent<TransformComponent>();

		SDL_FRect destRect{
			.x = transform->position.x,
			.y = transform->position.y,
			.w = static_cast<float>(m_width) * transform->scale.x,
			.h = static_cast<float>(m_height) * transform->scale.y
		};

		SDL_RenderTexture(renderer, m_texture, nullptr, &destRect);
	}
}