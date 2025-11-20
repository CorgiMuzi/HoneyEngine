#pragma once
#include "core/ManagerBase.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <SDL3_image/SDL_image.h>

struct SDL_Renderer;

namespace HoneyEngine
{
	class ResourceManager;
	class IRenderableComponent; // Forward Declaration

	class RenderManager final : public ManagerBase
	{
		struct TextureDeleter {
			void operator()(SDL_Texture* texture) const {
				if (texture) {
					SDL_DestroyTexture(texture);
				}
			}
		};

	public:
		explicit RenderManager(SDL_Renderer* renderer, ResourceManager* resourceManager);
		~RenderManager() override;

		RenderManager(const RenderManager&) = delete;
		RenderManager& operator=(const RenderManager&) = delete;

		/**
		 * @brief Clears the screen with a default color.
		 */
		void clearScreen();
		void clearScreen(const SDL_Color& color);
		void clearScreen(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		/**
		 * Registers renderable components to the render every frame
		 * @param targetComponent The renderable object target to register at the render manager.
		 */
		void registerComponent(IRenderableComponent& targetComponent);

		/**
		 * Unregisters renderable components from the cache.
		 * @param targetComponent The renderable object target to unreigster from the render manager.
		 */
		void unregisterComponent(IRenderableComponent& targetComponent);

		/**
		 * @brief Renders all registered renderable components.
		 */
		void renderAll();

		/**
		 * @brief Presents the final rendered image to the screen.
		 * (This should be called once at the end of each frame's rendering)
		 */
		void present();

		void term() override;

		void setClearColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) { m_clearColor = { r, g, b, a }; }
		SDL_Color getClearColor() const { return m_clearColor; }

		SDL_Renderer* getRenderer() const { return m_renderer; }

		/**
		 * @brief Gets a texture from the cache or loads it if not present.
		 * @param filePath The file path of the texture.
		 * @return A pointer to the SDL_Texture, or nullptr if loading fails.
		 */
		SDL_Texture* getTexture(const std::string& filePath);

	private:
		/**
		 * @brief Creates a texture from the file system and adds it to the cache.
		 * @param filePath The file path of the texture to load.
		 * @return True when create a texture successfully, or false when already texture exists in the cache or failed to create texture.
		 */
		SDL_Texture* createTexture(const std::string& filePath);

		// Default color for clearing the screen
		SDL_Color m_clearColor{ 0, 0, 0, 255 };

		SDL_Renderer* m_renderer;
		ResourceManager* m_resourceManager;

		/**
		 * @brief Cache for loaded textures
		 * All objects or components check this cache when needs to render a texture.
		 */
		std::unordered_map<std::string, std::unique_ptr<SDL_Texture, TextureDeleter>> m_textureCache;

		/**
		 * @brief A collection of renderable components
		 * All renderable components are self-registered to this vector.
		 * Use 'registerComponent(IRenderableComponent*)' to register renderable components manually
		 */
		std::vector<IRenderableComponent*> m_renderComponents;
	};
}