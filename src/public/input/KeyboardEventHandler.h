#pragma once
#include "interface/IEventHandler.h"

/**
 * @brief Handles keyboard events occurred in the SDL main loop
 */
class KeyboardEventHandler : public IEventHandler {
public:
    EEngineStatus handleEvent(const SDL_Event& event) override;
};