#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Components/CRenderingComponent.h"

#include "CRenderingSystem.h"

CRenderingSystem::CRenderingSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CRenderingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> renderingComponent;

	for (ex::Entity entity : entities.entities_with_components(renderingComponent))
	{
		this->target.draw(*renderingComponent.get());
	}
}