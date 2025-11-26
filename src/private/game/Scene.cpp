#include "game/Scene.h"

// Temporal headers for testing
#include "components/SpriteRendererComponent.h"

namespace HoneyEngine
{
	Scene::Scene(const std::string& name) : m_name(name){
		if (m_name.empty()) m_name = "Untitled Scene" + std::to_string(reinterpret_cast<uintptr_t>(this));
		m_world = std::make_unique<GameObject>(name, nullptr);
	}

	void Scene::init() {
		auto player = std::make_unique<GameObject>("Player", nullptr);
		GameObject* pPlayer = player.get();
		m_gameObjects.emplace_back(std::move(player));

		SpriteRendererComponent* comp = pPlayer->addComponent<SpriteRendererComponent>();
		comp->setSprite("asset/Characters/Units/Red Units/Warrior/Warrior_Idle.png");
	}

	void Scene::lateInit() {
		for (const auto& object : m_gameObjects) {
			if (object->getParent() == nullptr) {
				object->setParent(m_world.get());
			}
		}
	}

	void Scene::update(float deltaTime) {
		for (const auto& object : m_gameObjects) {
			object->update(deltaTime);
		}
	}

	void Scene::lateUpdate(float deltaTime) {
		for (const auto& object : m_gameObjects) {
			// TODO: Each objects perform lateUpdate if it needed
		}
	}

	void Scene::finalize() {

	}

	void Scene::destroy() {
		for (const auto& object : m_gameObjects) {
			// Unload objects from the memory
		}
	}
}