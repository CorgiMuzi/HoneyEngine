#pragma once
#include <memory>
#include <vector>
#include "EngineTypes.h"

// Forward declarations
class SDL_Window;
class SDL_Renderer;
class IEventHandler;
class IManagerBase;

class EngineCore {
public:
    static EngineCore& getInstance() {
        static EngineCore instance;
        return instance;
    }

    EngineCore(const EngineCore&) = delete;
    EngineCore& operator=(const EngineCore&) = delete;

    /**
     * @brief Initializes the SDL subsystem and creates a window.
     * @param w_width The width of the window
     * @param w_height The height of the window
     * @return True if initialization was successful, false otherwise
     */
    bool initEngine(int w_width, int w_height);

    /**
     * @brief Starts and runs the main game loop until the engine is stopped
     */
    void runEngine();

    /**
     * @brief Cleans up all engine resources and shuts down the SDL subsystem
     */
    void termEngine();

    void addEventHandler(std::unique_ptr<IEventHandler> handler);

private:
    EngineCore();
    ~EngineCore();

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

    bool m_isRunning{false};
    EEngineStatus m_currentStatus{EEngineStatus::Running};

    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};

    std::vector<std::unique_ptr<ManagerBase>> m_managers;
    std::vector<std::unique_ptr<IEventHandler>> m_eventHandlers;
};