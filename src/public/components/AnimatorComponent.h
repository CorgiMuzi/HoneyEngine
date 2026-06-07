#pragma once
#include "IComponent.h"
#include "resource/Animation.h"
#include <memory>

namespace HoneyEngine {
    class GameObject;

    class AnimatorComponent final : public IComponent {
    public:
        explicit AnimatorComponent(GameObject* owner);
        ~AnimatorComponent() override = default;

        void init(GameObject* owner) override;
        void update(float deltaTime) override;

        void play();
        void stop();
        void pause();
        void resume();

        void setAnimation(std::shared_ptr<Animation> animation);

    private:
        std::shared_ptr<Animation> m_animation{nullptr};
        size_t m_currentFrame{0};
        float m_elapsedTime{0.0f};

        bool m_isPlaying{false};
    };
}
