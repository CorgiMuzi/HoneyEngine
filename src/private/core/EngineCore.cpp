#include <SDL3/SDL.h>
#include "core/EngineCore.h"
#include "input/KeyboardEventHandler.h"


bool EngineCore::initEngine(int w_width, int w_height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL.\nERROR: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("HoneyEngine", w_width, w_height, SDL_WINDOW_RESIZABLE);

    if (!m_window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window.\nERROR: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);

    if (!m_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create renderer.\nERROR: %s", SDL_GetError());
        return false;
    }

    // Add event handlers
    addEventHandler(std::make_unique<KeyboardEventHandler>());

    return true;
}

void EngineCore::runEngine() {
    m_isRunning = true;
    EEngineStatus currentStatus = EEngineStatus::Running;

    while (m_isRunning) {
        currentStatus = processEvents();
        if (currentStatus != EEngineStatus::Running) {
            m_isRunning = false;
            continue;
        }

        currentStatus = update();
        if (currentStatus != EEngineStatus::Running) {
            m_isRunning = false;
            continue;
        }

        render();
    }

    handleShutdown(currentStatus);
}

EEngineStatus EngineCore::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                return EEngineStatus::Quit;
            case SDL_EVENT_WINDOW_RESIZED:
                // TODO: Handle window resize event
                // How can I control w_width, w_height??
                break;
            default:
                break;
        }
    }

    return EEngineStatus::Running;
}

EEngineStatus EngineCore::update() {
    // TODO: Update textures or other physical logic
    return EEngineStatus::Running;
}

void EngineCore::render() {
    // TODO: Render character texture and tiles
    SDL_SetRenderDrawColor(m_renderer, 20, 10, 30, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void EngineCore::handleShutdown(const EEngineStatus finalStatus) {
    if (finalStatus == EEngineStatus::Error) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error occurred. Engine terminated.\nERROR : %s", SDL_GetError());
        return;
    }

    if (finalStatus == EEngineStatus::Quit) {
        termEngine();
        return;
    }
}

void EngineCore::termEngine() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void EngineCore::addEventHandler(std::unique_ptr<IEventHandler> handler) {
    m_eventHandlers.emplace_back(std::move(handler));
}

EngineCore::EngineCore() = default;
EngineCore::~EngineCore() = default;
