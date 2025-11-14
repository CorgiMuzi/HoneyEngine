#pragma once

#include <vector>
#include <memory>

// Forward declarations
struct SDL_Renderer;
class ResourceManager;
class RenderManager;
class GameObject;

/**
 * @brief
 */
class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    /**
     * @brief Initializes the scene, including all game objects within it.
     * @param resManager A pointer to the ResourceManager, used for loading and managing assets.
     * @param renManager A pointer to the RenderManager, used for handling rendering operations.
     */
    void init(ResourceManager* resManager, RenderManager* renManager);

    /**
     * @brief Updates the state of the scene and all game objects.
     * @param deltaTime The time elapsed since the last frame, in seconds.
     */
    void update(float deltaTime);

    /**
     * @brief Renders the scene and all game objects to the provided renderer.
     * @param renderer A pointer to the SDL_Renderer to use for drawing.
     */
    void render(SDL_Renderer* renderer);

private:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};