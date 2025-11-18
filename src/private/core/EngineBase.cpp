#include <SDL3/SDL.h>
#include "core/EngineBase.h"

#include "components/SpriteRendererComponent.h"
#include "input/KeyboardEventHandler.h"
#include "resource/ResourceManager.h"
#include "render/RenderManager.h"

#include "gameplay/GameObject.h"
#include "resource/Surface.h"
#include <vector>

namespace HoneyEngine
{
	bool EngineBase::initEngine(int w_width, int w_height) {
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

		// Initialize managers
		{
			auto resourceManager = std::make_unique<ResourceManager>();
			/* Note TEST_PlayerRendering
			 * Delete below code after finishing test of rendering player
			 */
			const std::vector<std::string> exts{".png", ".jpeg", ".jpg", ".bmp"};
			resourceManager->registerResourceType<Surface>(exts);

			ResourceManager* pResourceManager = resourceManager.get();
			m_managers.emplace_back(std::move(resourceManager));

			auto renderManager = std::make_unique<RenderManager>(m_renderer, pResourceManager);
			m_managers.emplace_back(std::move(renderManager));

			for (const auto& manager : m_managers) {
				if (!manager->init()) {
					SDL_LogError(SDL_LOG_CATEGORY_ERROR, "A manager failed to initialize.");
					return false;
				}
			}
		}

		// Add event handlers
		addEventHandler(std::make_unique<KeyboardEventHandler>());

		return true;
	}

	void EngineBase::runEngine() {
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

	EEngineStatus EngineBase::processEvents() {
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

	EEngineStatus EngineBase::update() {
		// TODO: Update textures or other physical logic
		return EEngineStatus::Running;
	}

	void EngineBase::render() {
		// TODO: Render character texture and tiles
		RenderManager* renderManager = getManager<RenderManager>();
		if (!renderManager) return;

		renderManager->setClearColor(20, 10, 30, 255);
		renderManager->clearScreen();

		/* Note TEST_PlayerRendering
		 * Delete below code after finishing test of rendering player
		 */
		GameObject player;
		player.addComponent<SpriteRendererComponent>()->setTexture("asset/Characters/Units/Red Units/Warrior/Warrior_Idle.png");
		player.render(renderManager);

		renderManager->present();
	}

	void EngineBase::handleShutdown(const EEngineStatus finalStatus) {
		if (finalStatus == EEngineStatus::Error) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error occurred. Engine terminated.\nERROR : %s", SDL_GetError());
			return;
		}

		if (finalStatus == EEngineStatus::Quit) {
			termEngine();
			return;
		}
	}

	void EngineBase::termEngine() const {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}

	void EngineBase::addEventHandler(std::unique_ptr<IEventHandler> handler) {
		m_eventHandlers.emplace_back(std::move(handler));
	}

	EngineBase::EngineBase() = default;
	EngineBase::~EngineBase() {}
}