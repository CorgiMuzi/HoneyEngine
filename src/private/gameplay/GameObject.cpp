#include "gameplay/GameObject.h"
#include "render/RenderManager.h"
#include "components/TransformComponent.h"
#include "components/IRenderableComponent.h"
#include "components/SpriteRendererComponent.h"

namespace HoneyEngine
{
	GameObject::GameObject()
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

	void GameObject::render(RenderManager* renderManager) {
		for (const auto& component : m_components) {
			if (auto renderable = dynamic_cast<SpriteRendererComponent*>(component.get()); renderable) {
				renderable->render(renderManager);
			}
		}
	}
}
