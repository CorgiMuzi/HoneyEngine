#pragma once

#include <cassert>

// Forward declarations
struct SDL_Renderer;

namespace HoneyEngine
{
	class GameObject;

	class IComponent {
	public:
		virtual ~IComponent() = default;

		/**
		 * Initialize a component
		 */
		virtual void init(GameObject* owner) {
			setOwner(owner);
		}

		/**
		 * Update a component
		 * @param deltaTime The time since the last frame
		 */
		virtual void update(float deltaTime) {}

		void setOwner(GameObject* owner) { m_owner = owner; }
		GameObject* getOwner() const {
			assert(m_owner != nullptr && "Component must have an owner before used");
			return m_owner;
		}

	private:
		GameObject* m_owner{ nullptr };
	};
}