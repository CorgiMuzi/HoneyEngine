//
// Created by Jiheon on 2026-06-08.
//
#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

class SDL_Window;
class SDL_Renderer;

struct SWindowDeleter {
    void operator()(SDL_Window* W) const { SDL_DestroyWindow(W); }
};

struct SRendererDeleter {
    void operator()(SDL_Renderer* R) const { SDL_DestroyRenderer(R); }
};

struct SRenderContext {
    std::pair<std::unique_ptr<SDL_Window, SWindowDeleter>, std::unique_ptr<SDL_Renderer, SRendererDeleter>> Context;


};

class Application {

public:
    Application();
    ~Application();

    SDL_Window* CreateWindow();

private:
    std::vector<std::unique_ptr<SDL_Window, SWindowDeleter>> Windows;
    std::vector<std::unique_ptr<SDL_Renderer, SRendererDeleter>> Renderers;

public:
    std::vector<std::unique_ptr<SDL_Window, SWindowDeleter>>& GetWindows() { return Windows; }
};