#pragma once
#include <vector>
#include "resource/Texture.h"
#include "render/Sprite.h"

namespace HoneyEngine
{
	class Animation {
	public:
		explicit Animation(Texture* texture, int unitW, int unitH, int frameCount) : m_texture(texture){

		}

		/**
		 * @brief Should animation be looped.
		 */
		bool isLooping{false};

	private:
		Texture* m_texture;
		std::vector<Sprite> m_sprites;
	};
}