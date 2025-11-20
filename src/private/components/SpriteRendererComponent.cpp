#include "components/SpriteRendererComponent.h"
#include "render/RenderManager.h"
#include "gameplay/GameObject.h"
#include "components/TransformComponent.h"
#include "core/EngineBase.h"
#include <SDL3/SDL.h>

namespace HoneyEngine {
    SpriteRendererComponent::SpriteRendererComponent(GameObject* owner) {
    }

    SpriteRendererComponent::~SpriteRendererComponent() {
        if (auto* renderManager = EngineBase::getInstance()->getManager<RenderManager>()) {
            renderManager->unregisterComponent(*this);
        }
    }

    void SpriteRendererComponent::init(GameObject* owner) {
        IRenderableComponent::init(owner);
    }

    void SpriteRendererComponent::update(float deltaTime) {

    }

    void SpriteRendererComponent::render(RenderManager* renderManager) {
        if (m_texturePath.empty() || !renderManager) return;

        SDL_Texture* texture = renderManager->getTexture(m_texturePath);
        if (!texture) {
			SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Failed to get texture: %s", m_texturePath.c_str());
        	return;
        }

        TransformComponent* transform = getOwner()->getComponent<TransformComponent>();
        if (!transform) return;

        SDL_PropertiesID tex_props = SDL_GetTextureProperties(texture);
        float tex_w = SDL_GetFloatProperty(tex_props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0.f);
        float tex_h = SDL_GetFloatProperty(tex_props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0.f);

        SDL_FRect destRect{
            .x = transform->position.x,
            .y = transform->position.y,
            .w = tex_w,
            .h = tex_h
        };

        SDL_RenderTexture(renderManager->getRenderer(), texture, nullptr, &destRect);
    }
}