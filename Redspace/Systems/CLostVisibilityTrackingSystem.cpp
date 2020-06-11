#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Events/CLostVisibilityEvent.h"
#include "../Components/CRenderingComponent.h"

#include "CLostVisibilityTrackingSystem.h"

CLostVisibilityTrackingSystem::CLostVisibilityTrackingSystem(sf::RenderWindow& target, ex::Entity::Id mapId)
	: target(target), mapId(mapId)
{ }

void CLostVisibilityTrackingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity map = entities.get(this->mapId);

	ex::ComponentHandle<CRenderingComponent> mapRenderingComponent = map.component<CRenderingComponent>();
	sf::FloatRect mapGlobalBounds = mapRenderingComponent->getGlobalBounds();

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent))
	{
		sf::FloatRect entityGlobalBounds = entityRenderingComponent->getGlobalBounds();

		if (!mapGlobalBounds.intersects(entityGlobalBounds))
		{
			events.emit<CLostVisibilityEvent>(entity);
		}
	}
}
