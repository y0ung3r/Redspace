#include "CRenderSystem.h"

void CRenderSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderComponent> renderComponent;

	for (ex::Entity entity : entities.entities_with_components(renderComponent))
	{
		this->target.draw(*renderComponent.get());
	}
}