#pragma once
#include <vector>
#include "resource/Resource.h"
#include "resource/Texture.h"
#include "render/Sprite.h"

namespace HoneyEngine
{
	class Animation final : public Resource {
	public:
		explicit Animation(const std::string& filePath) : Resource(filePath) {}
		void addFrame(const Sprite& sprite);
		void addFrame(const std::shared_ptr<Texture>& texture, float srcX, float srcY, float spriteWidth, float spriteHeight);
		void addFrameFromSpriteSheet(const std::shared_ptr<Texture>& texture, float frameWidth, float frameHeight, int frameCount, float srcX, float srcY, float paddingX, float paddingY);
		const Sprite& getFrame(size_t index) const;

	private:
		/**
		 * @brief Frames per seconds
		 */
		float m_frameRate{10.f};

		/**
		 * @brief Should animation be looped.
		 */
		bool m_isLooping{false};

		std::vector<Sprite> m_frames;

	public:
		size_t getFrameCount() const { return m_frames.size(); }

		bool isLooping() const { return m_isLooping; }
		void setLooping(const bool bisLoop) { m_isLooping = bisLoop; }

		float getFrameRate() const { return m_frameRate; }
		void setFrameRate(const float frameRate) { m_frameRate = frameRate; }
	};
}