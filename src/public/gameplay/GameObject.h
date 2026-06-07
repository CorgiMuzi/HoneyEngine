#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <string>

#include "components/IComponent.h"
#include "utils/INamedObject.h"

struct SDL_Renderer;

namespace HoneyEngine
{
	class RenderManager;

	/**
	 * @brief Represents a base object in the game world that can hold various components.
	 */
	class GameObject : public INamedObject {
	public:
		/**
		 * @brief Constructs a new GameObject.
		 * @param name The name of the GameObject.
		 * @param parent A pointer to the parent GameObject. If is the root object, pass SceneManager::getWorldObject() as the parent.
		 */
		explicit GameObject(const std::string& name, GameObject* parent);
		~GameObject();

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		void update(float deltaTime);

		// TODO(human): Update addComponent to generate component names
		// You might want to include the GameObject's name in the component name
		// Example: getName() + ".SpriteRenderer" or just "SpriteRenderer#12345"
		template<typename T, typename... TArgs>
		T* addComponent(TArgs&&... args) {
			static_assert(std::is_base_of_v<IComponent, T>, "T must be a descendant of IComponent");

			std::unique_ptr<T> newComponent = std::make_unique<T>(this, std::forward<TArgs>(args)...);
			T* pComponent = newComponent.get();

			m_components.emplace_back(std::move(newComponent));
			pComponent->init(this);
			return pComponent;
		}

		template<typename T>
		T* getComponent() {
			for (const auto& component : m_components) {
				if (T* target = dynamic_cast<T*>(component.get())) {
					return target;
				}
			}

			return nullptr;
		}

		// getName() is now inherited from INamedObject
		// No need for m_name member anymore as it's in INamedObject::m_namedID

		void setParent(GameObject* parent) { m_parent = parent; }
		GameObject* getParent() const { return m_parent; }

	private:
		GameObject* m_parent;
		// TODO(human): Remove m_name member - it's now handled by INamedObject::m_namedID
		std::vector<std::unique_ptr<IComponent>> m_components;
	};
}