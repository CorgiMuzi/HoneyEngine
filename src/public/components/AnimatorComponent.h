#pragma once
#include "IComponent.h"
#include "SpriteRendererComponent.h"

namespace HoneyEngine {
    class AnimatorComponent final : public IComponent {
    public:
        explicit AnimatorComponent() {};
        ~AnimatorComponent() override = default;

        void init(GameObject* owner) override;
        void update(float deltaTime) override;

    private:
        SpriteRendererComponent* m_spriteRenderer{nullptr};
    };
}
