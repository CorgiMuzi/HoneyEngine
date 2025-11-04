#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <SDL3/SDL.h>

class Animation;

enum class ObjectType {
    EOT_Player,
    EOT_Level,
    EOT_Enemy
};

class GameObject {
public:
    GameObject();

    ObjectType type;
    float direction;
    glm::vec2 position, velocity, acceleration;
    std::vector<Animation*> animations;
    int currentAnimation;
    SDL_Texture* texture;
};