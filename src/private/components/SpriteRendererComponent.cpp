#include "components/SpriteRendererComponent.h"
#include "components/TransformComponent.h"
#include "core/EngineBase.h"
#include "render/RenderManager.h"
#include "resource/ResourceManager.h"
#include "gameplay/GameObject.h"
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
        if (!m_sprite || !renderManager) return;

        const auto* transform = getOwner()->getComponent<TransformComponent>();
        if (!transform) return;

        SDL_Renderer* renderer = renderManager->getRenderer();
        if (!renderer) return;

        SDL_Texture* texture = m_sprite->getTexture();
        if (!texture) return;

        const SDL_FRect srcRect = m_sprite->getSrcRect();

        SDL_FRect dstRect;
        const float spriteWidth = (srcRect.w > 0) ? srcRect.w : m_sprite->getWidth();
        const float spriteHeight = (srcRect.h > 0) ? srcRect.h : m_sprite->getHeight();

        dstRect.w = spriteWidth * transform->scale.x;
        dstRect.h = spriteHeight * transform->scale.y;
        dstRect.x = transform->position.x;
        dstRect.y = transform->position.y;

        const SDL_FRect* srcRectPtr = (srcRect.w > 0 && srcRect.h > 0) ? &srcRect : nullptr;

        if (transform->rotation != 0.0f) {
            SDL_RenderTextureRotated(renderer, texture, srcRectPtr, &dstRect,
                                     transform->rotation, nullptr, SDL_FLIP_NONE);
        } else {
            SDL_RenderTexture(renderer, texture, srcRectPtr, &dstRect);
        }
    }

    void SpriteRendererComponent::setSprite(std::unique_ptr<Sprite> sprite) {
        m_sprite = std::move(sprite);
    }

    void SpriteRendererComponent::setSprite(const std::string& filePath) {
        ResourceManager* resourceManager = EngineBase::getInstance()->getManager<ResourceManager>();
        if (!resourceManager) return;

        auto texture = resourceManager->load<Texture>(filePath);
        m_sprite = std::make_unique<Sprite>(texture);
    }

    void SpriteRendererComponent::setSprite(const std::string& filePath, float x, float y, float width, float height) {
        ResourceManager* resourceManager = EngineBase::getInstance()->getManager<ResourceManager>();
        if (!resourceManager) return;

        auto texture = resourceManager->load<Texture>(filePath);
        m_sprite = std::make_unique<Sprite>(texture, x, y, width, height);
    }
}
