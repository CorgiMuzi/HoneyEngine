#include "gameplay/GameObject.h"

void GameObject::update(float deltaTime) {
    for (const auto& component : m_components) {
        component->update(deltaTime);
    }
}

void GameObject::render(SDL_Renderer* renderer) {
    for (const auto& component : m_components) {
        component->render(renderer);
    }
}

