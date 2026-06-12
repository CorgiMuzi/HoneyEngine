//
// Created by Jiheon on 2026-06-08.
//
#pragma once

#include <memory>
#include <SDL3/SDL_events.h>

class Application;
class SDL_Window;

class HoneyEngine {
public:
    HoneyEngine();
    ~HoneyEngine();

    void Run();

private:
    void ProcessEvent(SDL_Event& Event);
    void RenderScreen();

    std::unique_ptr<Application> App;
    SDL_Window* Window;
    bool bIsRunning{false};
};
