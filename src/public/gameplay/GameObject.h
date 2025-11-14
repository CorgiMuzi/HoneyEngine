#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "core/IComponent.h"

// Forward declarations
struct SDL_Renderer;

/**
 * @brief Represents a base object in the game world that can hold various components.
 */
class GameObject {
public:
    GameObject() = default;
    ~GameObject() = default;

    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject&) = delete;

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);

    template<typename T, typename... TArgs>
    T* addComponent(TArgs&&... args) {
        static_assert(std::is_base_of<IComponent, T>::value, "T must be a descendant of IComponent");

        std::unique_ptr<T> newComponent = std::make_unique<T>(std::forward<TArgs>(args)...);
        T* pComponent = newComponent.get();
        newComponent->setOwner(this);

        m_components.emplace_back(std::move(newComponent));
        pComponent->init();
        return pComponent;
    }

    template<typename T>
    T* getComponent() {
        for (const auto& component : m_components) {
            if (T* target = dynamic_cast<T*>(component.get())) {
                return target;
            }
        }

        return nullptr;
    }

private:
    std::vector<std::unique_ptr<IComponent>> m_components;
};