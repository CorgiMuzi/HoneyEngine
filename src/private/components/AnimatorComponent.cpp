#include "components/AnimatorComponent.h"
#include "components/SpriteRendererComponent.h"
#include "gameplay/GameObject.h"
#include <iostream>

namespace HoneyEngine {
    AnimatorComponent::AnimatorComponent(GameObject* owner) {
    }

    void AnimatorComponent::init(GameObject* owner) {
        IComponent::init(owner);
    }

    void AnimatorComponent::update(float deltaTime) {
        IComponent::update(deltaTime);

        static int updateCount = 0;
        updateCount++;
        if (updateCount <= 5) {
            std::cout << "AnimatorComponent::update called (deltaTime=" << deltaTime << ", m_isPlaying=" << m_isPlaying << ")" << std::endl;
        }

        // Early exit if not playing or no animation
        if (!m_isPlaying) {
            static bool warned = false;
            if (!warned) {
                std::cout << "AnimatorComponent: Not playing" << std::endl;
                warned = true;
            }
            return;
        }

        if (!m_animation || m_animation->getFrameCount() == 0) {
            static bool warned = false;
            if (!warned) {
                std::cout << "AnimatorComponent: No animation or no frames" << std::endl;
                warned = true;
            }
            return;
        }

        // Accumulate elapsed time
        m_elapsedTime += deltaTime;

        // Calculate frame duration (how long each frame should be displayed)
        const float frameDuration = 1.0f / m_animation->getFrameRate();

        // Advance frames if enough time has passed
        if (m_elapsedTime >= frameDuration) {
            // Subtract frame duration (not reset to 0, to handle deltaTime > frameDuration)
            m_elapsedTime -= frameDuration;

            m_currentFrame++;

            // Handle end of animation
            if (m_currentFrame >= m_animation->getFrameCount()) {
                if (m_animation->isLooping()) {
                    m_currentFrame = 0;
                } else {
                    // Stop at the last frame
                    m_currentFrame = m_animation->getFrameCount() - 1;
                    m_isPlaying = false;
                }
            }

            // Update the sprite renderer with the current frame
            if (auto* spriteRenderer = getOwner()->getComponent<SpriteRendererComponent>()) {
                spriteRenderer->setSprite(m_animation->getFrame(m_currentFrame));
            }
        }
    }

    void AnimatorComponent::setAnimation(std::shared_ptr<Animation> animation) {
        m_animation = std::move(animation);
        m_currentFrame = 0;
        m_elapsedTime = 0.0f;

        // Set the initial frame immediately
        if (m_animation && m_animation->getFrameCount() > 0) {
            if (auto* spriteRenderer = getOwner()->getComponent<SpriteRendererComponent>()) {
                spriteRenderer->setSprite(m_animation->getFrame(0));
            } else {
                std::cout << "AnimatorComponent: WARNING - No SpriteRendererComponent found!" << std::endl;
            }
        }
    }

    void AnimatorComponent::play() {
        m_isPlaying = true;
        m_currentFrame = 0;
        m_elapsedTime = 0.0f;

        // Set the initial frame immediately when starting playback
        if (m_animation && m_animation->getFrameCount() > 0) {
            if (auto* spriteRenderer = getOwner()->getComponent<SpriteRendererComponent>()) {
                spriteRenderer->setSprite(m_animation->getFrame(0));
            }
        }
    }

    void AnimatorComponent::stop() {
        m_isPlaying = false;
        m_currentFrame = 0;
        m_elapsedTime = 0.0f;
    }

    void AnimatorComponent::pause() {
        m_isPlaying = false;
    }

    void AnimatorComponent::resume() {
        m_isPlaying = true;
    }
}
