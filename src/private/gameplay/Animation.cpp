#include "gameplay/Animation.h"
#include <format>
#include <iostream>
#include <cassert>
#include <stdexcept>

namespace HoneyEngine {
    void Animation::addFrame(const Sprite& sprite) {
        m_frames.emplace_back(sprite);
    }

    void Animation::addFrame(const std::shared_ptr<Texture>& texture, const float srcX, const float srcY, const float spriteWidth,
        const float spriteHeight) {
        m_frames.emplace_back(texture, srcX, srcY, spriteWidth, spriteHeight);
    }

    void Animation::addFrameFromSpriteSheet(const std::shared_ptr<Texture>& texture, const float frameWidth, const float frameHeight,
                                            const int frameCount, const float srcX, const float srcY, const float paddingX, const float paddingY) {
        if (!texture->getTexture()) {
            const std::string err = std::format("Animation '{}': Source texture is missing. Failed to create Animation from sprites.", getFilePath());
            std::cerr << err << std::endl;

            assert(false && "Failed to create animation. See console for details.");
            return;
        }

        m_frames.clear();

        const glm::vec2 texSize = texture->getTextureSize();
        float curX = srcX;
        float curY = srcY;

        for (int i = 0; i < frameCount; ++i) {
            if (curX + frameWidth > texSize.x) {
                curX = srcX;
                curY += (frameHeight + paddingY);
            }

            if (curY + frameHeight > texSize.y) {
                break;
            }

            addFrame(texture, curX, curY, frameWidth, frameHeight);
            curX += (frameWidth + paddingX);
        }
    }

    const Sprite& Animation::getFrame(size_t index) const {
        if (index >= m_frames.size()) {
            const std::string err = std::format("Animation '{}': Frame index {} out of bounds (Size: {}).", getFilePath(),
                                          index, m_frames.size());
            std::cerr << err << std::endl;

            assert(false && "Animation Frame index out of bounds! See console for details.");

            if (m_frames.empty()) {
                throw std::runtime_error(err);
            }
            return m_frames.back();
        }

        return m_frames[index];
    }
}
