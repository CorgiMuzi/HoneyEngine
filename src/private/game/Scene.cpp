#include "game/Scene.h"

#include <SDL3/SDL_render.h>

#include "resource/ResourceManager.h"
#include "render/RenderManager.h"

namespace HoneyEngine
{
	void Scene::init(ResourceManager* resManager, RenderManager* renManager) {
		const std::string characterTexturePath = "asset/Characters/Units/Red Units/Warrior/Warrior_Idle.png";

		if (resManager) auto characterResource = resManager->loadResource(characterTexturePath);

	}

	void Scene::update(float deltaTime) {
	}

	void Scene::render(SDL_Renderer* renderer) {
	}
}