#include "game/Scene.h"

// Temporal headers for testing
#include "components/SpriteRendererComponent.h"
#include "components/AnimatorComponent.h"
#include "components/TransformComponent.h"
#include "resource/Animation.h"
#include "core/EngineBase.h"
#include "resource/ResourceManager.h"
#include <iostream>

namespace HoneyEngine
{
	Scene::Scene(const std::string& name) : m_name(name){
		if (m_name.empty()) m_name = "Untitled Scene" + std::to_string(reinterpret_cast<uintptr_t>(this));
		m_world = std::make_unique<GameObject>(name, nullptr);
	}

	void Scene::init() {
		// Get the resource manager
		auto* resourceManager = EngineBase::getInstance()->getManager<ResourceManager>();
		if (!resourceManager) return;

		// Load the warrior idle sprite sheet texture
		auto warriorTexture = resourceManager->load<Texture>("asset/Characters/Units/Red Units/Warrior/Warrior_Idle.png");

		// Create the idle animation
		auto idleAnimation = std::make_shared<Animation>("Warrior_Idle");
		// The sprite sheet has 8 frames, each 150x150 pixels, arranged horizontally
		idleAnimation->addFrameFromSpriteSheet(warriorTexture, 192.0f, 192.0f, 8, 0.0f, 0.0f, 0.0f, 0.0f);
		idleAnimation->setFrameRate(8.0f);  // 8 FPS for smooth idle animation
		idleAnimation->setLooping(true);

		std::cout << "Animation created with " << idleAnimation->getFrameCount() << " frames" << std::endl;

		// Create the player GameObject (TransformComponent is automatically added)
		auto player = std::make_unique<GameObject>("Player", nullptr);
		GameObject* pPlayer = player.get();
		m_gameObjects.emplace_back(std::move(player));

		// Set position using the auto-created TransformComponent
		auto* transform = pPlayer->getComponent<TransformComponent>();
		transform->position = {400.f, 300.f};  // Center of screen (adjust as needed)

		// Add SpriteRenderer component to display the sprites
		pPlayer->addComponent<SpriteRendererComponent>();

		// Add Animator component and set the animation
		auto* animator = pPlayer->addComponent<AnimatorComponent>();
		animator->setAnimation(idleAnimation);
		animator->play();
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