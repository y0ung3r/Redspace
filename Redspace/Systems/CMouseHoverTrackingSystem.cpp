#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CMouseHoverEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"

#include "CMouseHoverTrackingSystem.h"

CMouseHoverTrackingSystem::CMouseHoverTrackingSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CMouseHoverTrackingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent))
	{
		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag != ObjectTypes::Map && entityTag != ObjectTypes::Camera)
		{
			sf::FloatRect entityGlobalBounds = entityRenderingComponent->getGlobalBounds();

			sf::Vector2f mousePosition = CGame::getMousePositionInCoords(this->target);

			if (entityGlobalBounds.contains(mousePosition))
			{
				events.emit<CMouseHoverEvent>(entity);
			}
		}
	}
}
