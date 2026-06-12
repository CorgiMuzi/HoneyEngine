//
// Created by Jiheon on 2026-06-08.
//

#include "core/HoneyEngine.h"

#include <iostream>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>

#include "core/Application.h"

HoneyEngine::HoneyEngine() {
    App = std::make_unique<Application>();
    Window = App->CreateWindow();
    if (Window == nullptr) {
        throw std::runtime_error("Failed to create window");
    }
}

HoneyEngine::~HoneyEngine() {
}

void HoneyEngine::Run() {
    SDL_Event Event;
    bIsRunning = true;
    while (bIsRunning) {
        ProcessEvent(Event);
        RenderScreen();
    }
}

void HoneyEngine::ProcessEvent(SDL_Event& Event) {
    while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_EVENT_QUIT) {
            bIsRunning = false;
        }
    }
}

void HoneyEngine::RenderScreen() {
    SDL_Renderer* RenderHandle = SDL_GetRenderer(Window);
    if (RenderHandle == nullptr) return;

    SDL_SetRenderDrawColor(RenderHandle, 255, 0, 0, 255);
    SDL_RenderClear(RenderHandle);
    SDL_RenderPresent(RenderHandle);
}