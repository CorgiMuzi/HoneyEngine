#include "components/IRenderableComponent.h"

#include "core/EngineBase.h"
#include "render/RenderManager.h"

namespace HoneyEngine {
    void IRenderableComponent::init(GameObject* owner) {
        IComponent::init(owner);

        if (auto* renderManager = EngineBase::getInstance()->getManager<RenderManager>()) {
            renderManager->registerComponent(*this);
        }
    }
}