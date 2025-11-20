#pragma once

#include <vector>
#include <memory>
#include <string>
#include "gameplay/GameObject.h"

namespace HoneyEngine
{
	class Scene {
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene() = default;

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

	public:
		/**
		 * @brief The first initialization function called when the scene is loaded.
		 * Responsible for resource loading and initial object creation.
		 */
		virtual void init();

		/**
		 * @brief Called once after all objects' init() calls are finished, just before the update().
		 * Used for setting up references between objects.
		 */
		virtual void lateInit();

		/**
		 * @brief Called every frame to update the main logic(e.g., gameplay logic, physics calculations, etc.) of the scene.
		 * @param deltaTime The time elapsed since the last frame, in seconds.
		 */
		virtual void update(float deltaTime);

		/**
		 * @brief Called every frame after all objects' update() calls are finished.
		 * Mainly used for post-processing logic like camera tracking.
		 * @param deltaTime The time elapsed since the last frame, in seconds.
		 */
		virtual void lateUpdate(float deltaTime);

		/**
		 * @brief Cleanup the objects' references just before destroy the all objects and the scene.
		 * Responsible for releasing used resources.
		 */
		virtual void finalize();

		/**
		 * @brief Destroys and releases all memory associated with the scene.
		 */
		virtual void destroy();

		const std::string& getName() const { return m_name; }
		const GameObject& getWorld() const { return *m_world; }

	private:
		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_gameObjects;
		std::unique_ptr<GameObject> m_world;
	};
}