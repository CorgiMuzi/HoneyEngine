#include <SDL3/SDL.h>
#include "input/KeyboardEventHandler.h"

namespace HoneyEngine
{
	EEngineStatus KeyboardEventHandler::handleEvent(const SDL_Event& event) {
		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_ESCAPE) {
				return EEngineStatus::Quit;
			}
		}

		return EEngineStatus::Running;
	}
}