#pragma once

#include "core/IComponent.h"
#include <glm/glm.hpp>

/**
 * @brief Manages the position, rotation and scale of a GameObject
 * Almost every GameObject will have a TransformComponent
 */
class TransformComponent : public IComponent {
public:
    TransformComponent(glm::vec2 position = glm::vec2(0.f, 0.f), float rotation = 0.f, glm::vec2 scale = glm::vec2(1.f, 1.f)) :
        position(position), rotation(rotation), scale(scale) {}

    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
};