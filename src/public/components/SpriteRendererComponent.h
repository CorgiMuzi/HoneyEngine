#pragma once

#include <memory>
#include "IRenderableComponent.h"
#include "render/Sprite.h"

struct SDL_Renderer;

namespace HoneyEngine {
    class GameObject;
    class RenderManager;

    /**
     * @brief Renders a sprite(texture) at the GameObject's position.
     * This component requires a TransformComponent to be present on the same GameObject.
     */
    class SpriteRendererComponent final : public IRenderableComponent {
    public:
        explicit SpriteRendererComponent(GameObject* owner);

        ~SpriteRendererComponent() override;

        void init(GameObject* owner) override;
        void update(float deltaTime) override;
        void render(RenderManager* renderManager) override;

    private:
        std::unique_ptr<Sprite> m_sprite;
        int m_width{0};
        int m_height{0};

    public:
    void setSprite(std::unique_ptr<Sprite> sprite);
    };
}
