#pragma once
#include "core/EngineTypes.h"
#include <SDL3/SDL_events.h>

class IEventHandler {
public:
    virtual ~IEventHandler() = default;

    virtual EEngineStatus handleEvent(const SDL_Event& event) = 0;
};
