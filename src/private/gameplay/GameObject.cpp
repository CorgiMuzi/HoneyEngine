#include "gameplay/GameObject.h"
#include "render/RenderManager.h"
#include "components/TransformComponent.h"
#include "components/SpriteRendererComponent.h"

namespace HoneyEngine
{
	// TODO(human): Update constructor to call INamedObject(name) instead of using m_name
	GameObject::GameObject(const std::string& name, GameObject* parent)
		: INamedObject(name), m_parent(parent)
	{
		addComponent<TransformComponent>();
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::update(float deltaTime) {
		for (const auto& component : m_components) {
			component->update(deltaTime);
		}
	}
}
