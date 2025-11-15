#include "components/TransformComponent.h"
#include "gameplay/GameObject.h"

namespace HoneyEngine
{
	TransformComponent::TransformComponent(GameObject* owner, glm::vec2 position, float rotation, glm::vec2 scale)
		: IComponent(), position(position), rotation(rotation), scale(scale)
	{
		setOwner(owner);
	}
}