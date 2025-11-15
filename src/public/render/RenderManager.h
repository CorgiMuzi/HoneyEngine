#pragma once
#include "core/ManagerBase.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <SDL3/SDL_pixels.h>

// Forward declarations
struct SDL_Texture;
struct SDL_Renderer;

namespace HoneyEngine
{
	class ResourceManager;

	class RenderManager final : public ManagerBase
	{
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
		 * @brief Presents the final rendered image to the screen.
		 * (This should be called once at the end of each frame's rendering)
		 */
		void present();

		/**
		 * @brief Draws a texture to the screen at a given position.
		 * @param filePath The file path of the texture to draw.
		 * @param x The x-coordinate to draw the texture at.
		 * @param y The y-coordinate to draw the texture at.
		 */
		void draw(const std::string& filePath, int x, int y);

		// TODO: Add more draw overloads for drawing with rotation, scaling, etc.
		// void draw(const std::string& filePath, int x, int y, double angle, ...);

		// ==== ManagerBase ====
		void term() override;
		// =====================

	private:
		/**
		 * @brief Gets a texture from the cache or loads it if not present
		 * @param filePath The file path of the texture
		 * @return A pointer to the SDL_Texture, or nullptr if loading fails
		 */
		SDL_Texture* getTexture(const std::string& filePath);

		/**
		 * @brief Creates a texture from the file system and adds it to the cache
		 * @param filePath The file path of the texture to load
		 * @return True when create a texture successfully, or false when already texture exists in the cache or failed to create texture
		 */
		SDL_Texture* createTexture(const std::string& filePath);

		// Default color for clearing the screen
		SDL_Color m_clearColor{ 0, 0, 0, 255 };

		SDL_Renderer* m_renderer;
		ResourceManager* m_resourceManager;

		std::unordered_map<std::string, std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>> m_textureCache;

	public:
		void setClearColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) { m_clearColor = { r, g, b, a }; }
		SDL_Color getClearColor() const { return m_clearColor; }
	};
}