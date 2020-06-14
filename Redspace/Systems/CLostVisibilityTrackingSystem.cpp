#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Events/CLostVisibilityEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Extensions/Collision.h"

#include "CLostVisibilityTrackingSystem.h"

CLostVisibilityTrackingSystem::CLostVisibilityTrackingSystem(CGame& game, sf::RenderWindow& target)
	: game(game), target(target)
{ }

void CLostVisibilityTrackingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity::Id mapId = this->game.getMapId();
	ex::Entity map = entities.get(mapId);

	ex::ComponentHandle<CRenderingComponent> mapRenderingComponent = map.component<CRenderingComponent>();
	sf::FloatRect mapGlobalBounds = mapRenderingComponent->getGlobalBounds();

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent))
	{
		sf::Sprite mapSprite = *mapRenderingComponent.get();
		sf::Sprite entitySprite = *entityRenderingComponent.get();

		if (entity && !Collision::BoundingBoxTest(mapSprite, entitySprite))
		{
			events.emit<CLostVisibilityEvent>(entity);
		}
	}
}
