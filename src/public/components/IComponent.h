#pragma once

#include <cassert>
#include "utils/INamedObject.h"

// Forward declarations
struct SDL_Renderer;

namespace HoneyEngine
{
	class GameObject;

	class IComponent : public INamedObject {
	public:
		// TODO(human): Update this constructor to accept a name parameter
		// The name should be generated based on the component type
		// Example: "SpriteRendererComponent#12345" or "Player.SpriteRenderer"
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

	private:
		GameObject* m_owner{ nullptr };

	public:
		void setOwner(GameObject* owner) { m_owner = owner; }
		GameObject* getOwner() const {
			assert(m_owner != nullptr && "Component must have an owner before used");
			return m_owner;
		}
	};
}