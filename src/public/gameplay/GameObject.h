#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <SDL3/SDL.h>

class Animation;

enum class EObjectType {
    EOT_Player,
    EOT_Level,
    EOT_Enemy
};

enum class EPlayerState {
    EPS_Idle,
    EPS_Run,
    EPS_Jump,
    EPS_Crouch
};

struct PlayerData {
    EPlayerState state;
};

struct LevelData {

};

struct EnemyData {

};

union ObjectData {
    PlayerData player;
    LevelData level;
    EnemyData enemy;
};

class GameObject {
public:
    GameObject();

    EObjectType type;
    ObjectData data;
    float direction;
    float maxSpeedX;
    glm::vec2 position, velocity, acceleration;
    std::vector<Animation*> animations;
    int currentAnimation;
    SDL_Texture* texture;
};