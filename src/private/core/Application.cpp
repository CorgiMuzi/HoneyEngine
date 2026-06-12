//
// Created by Jiheon on 2026-06-08.
//

#include <iostream>

#include "core/Application.h"
#include "SDL3/SDL.h"

Application::Application() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(SDL_GetError());
    }
}

Application::~Application() {
    SDL_Quit();
}

SDL_Window* Application::CreateWindow() {
    SDL_Window* Window = SDL_CreateWindow("HoneyEngine", 960, 720, SDL_WINDOW_OPENGL);
    Windows.emplace_back(std::unique_ptr<SDL_Window, SWindowDeleter>(Window));
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, "HoneyRenderer");
    Renderers.emplace_back(std::unique_ptr<SDL_Renderer, SRendererDeleter>(Renderer));

    return Window;
}
