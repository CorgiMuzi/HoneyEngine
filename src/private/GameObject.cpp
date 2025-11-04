#include "GameObject.h"
#include "Animation.h"

GameObject::GameObject()
{
    type = ObjectType::EOT_Level;
    direction = 1;
    position = velocity = acceleration = glm::vec2(0);

    currentAnimation = -1;
    texture = nullptr;
}

