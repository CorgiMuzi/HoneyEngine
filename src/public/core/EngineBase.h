#pragma once
#include <memory>
#include <vector>
#include "EngineTypes.h"

class SDL_Window;
class SDL_Renderer;

namespace HoneyEngine
{
	class IEventHandler;
	class ManagerBase;
	class Scene;

	class EngineBase {
	public:
		static EngineBase* getInstance() {
			static EngineBase instance;
			return &instance;
		}
		~EngineBase();

		EngineBase(const EngineBase&) = delete;
		EngineBase& operator=(const EngineBase&) = delete;

		/**
		 * @brief Initializes the SDL subsystem and creates a window.
		 * @param windowWidth The width of the window
		 * @param windowHeight The height of the window
		 * @return True if initialization was successful, false otherwise
		 */
		bool initEngine(int windowWidth, int windowHeight);

		/**
		 * @brief Starts and runs the main game loop until the engine is stopped
		 */
		void runEngine();

		/**
		 * @brief Cleans up all engine resources and shuts down the SDL subsystem
		 */
		void termEngine() const;

		void loadScene(std::unique_ptr<Scene> scene);

		void addEventHandler(std::unique_ptr<IEventHandler> handler);

		/**
		 * @brief Gets a manager of a specific type from the manager list
		 * @tparam T The type of the manager to get (e.g. RenderManager)
		 * @return A pointer to the manager if found, otherwise nullptr
		 */
		template<typename T>
		T* getManager() const {
			for (const auto& manager : m_managers) {
				if (T* result = dynamic_cast<T*>(manager.get())) {
					return result;
				}
			}

			return nullptr;
		}

	private:
		EngineBase();

		/**
		 * @brief Processes all pending events from the SDL event queue
		 */
		EEngineStatus processEvents();

		/**
		 * @brief Updates the logic and states for the current frame
		 */
		EEngineStatus update();

		/**
		 * @brief Render a single frame of the game
		 */
		void render();

		/**
		 * @brief Handles the shutdown process based on the final engine status.
		 * @param finalStatus The status that caused the engine to stop.
		 */
		void handleShutdown(EEngineStatus finalStatus);

		bool m_isRunning{ false };
		EEngineStatus m_currentStatus{ EEngineStatus::Running };

		SDL_Window* m_window{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };

		std::vector<std::unique_ptr<ManagerBase>> m_managers;
		std::vector<std::unique_ptr<IEventHandler>> m_eventHandlers;

		std::unique_ptr<Scene> m_currentScene{nullptr};
	};
}