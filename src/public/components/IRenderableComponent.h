#pragma once

#include "IComponent.h"

struct SDL_Renderer;

namespace HoneyEngine {
    class RenderManager; // Forward Declaration

    class IRenderableComponent : public IComponent {
    public:
        virtual ~IRenderableComponent() override = default;

        void init(GameObject* owner) override;

        /**
         * @brief Renders the component to the screen using the provided renderer.
         * @param renderManager The SDL_Renderer context to use for all drawing operations.
         */
        virtual void render(RenderManager* renderManager) = 0;
    };
}