#pragma once
#include "interface/IEventHandler.h"

namespace HoneyEngine
{
	/**
	 * @brief Handles keyboard events occurred in the SDL main loop
	 */
	class KeyboardEventHandler : public IEventHandler {
	public:
		EEngineStatus handleEvent(const SDL_Event& event) override;
	};
}