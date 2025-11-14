#pragma once

#include "core/IComponent.h"

// Forward declarations
struct SDL_Texture;
struct SDL_Renderer;

/**
 * @brief Renders a sprite(texture) at the GameObject's position
 * This component requires a TransformComponent to be present on the same GameObject
 */
class SpriteRendererComponent : public IComponent {
public:
    explicit SpriteRendererComponent(SDL_Texture* texture);

    void init() override;
    void render(SDL_Renderer* renderer) override;

private:
    SDL_Texture* m_texture;
    int m_width{0.f};
    int m_height{0.f};
};