#pragma once

#include <string>
#include "IRenderableComponent.h"

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

        void setTexture(const std::string& texturePath) { m_texturePath = texturePath; }

    private:
        std::string m_texturePath;
        int m_width{0};
        int m_height{0};
    };
}
