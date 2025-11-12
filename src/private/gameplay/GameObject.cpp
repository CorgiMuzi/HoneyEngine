#include "gameplay/GameObject.h"
#include "gameplay/Animation.h"

GameObject::GameObject() : type(EObjectType::EOT_Level), data{.level = LevelData()}
{
    direction = 1;
    position = velocity = acceleration = glm::vec2(0);
    maxSpeedX = 0;

    currentAnimation = -1;
    texture = nullptr;
}

