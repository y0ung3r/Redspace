#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CMouseHoverEvent.h"
#include "../Events/CMouseExitEvent.h"
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

	sf::Vector2f mousePosition = CGame::getMousePositionInCoords(this->target);

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent))
	{
		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entity && entityTag != ObjectTypes::Map && entityTag != ObjectTypes::Camera)
		{
			sf::FloatRect entityGlobalBounds = entityRenderingComponent->getGlobalBounds();

			if (entityGlobalBounds.contains(mousePosition))
			{
				events.emit<CMouseHoverEvent>(entity);
				this->listOfHoveredObjects.push_back(entity);
			}
		}
	}

	for (ex::Entity hoveredObject : this->listOfHoveredObjects)
	{
		if (hoveredObject)
		{
			sf::FloatRect hoveredObjectGlobalBounds = hoveredObject.component<CRenderingComponent>()->getGlobalBounds();
			
			if (!hoveredObjectGlobalBounds.contains(mousePosition))
			{
				events.emit<CMouseExitEvent>(hoveredObject);

				auto objectIterator = std::find(this->listOfHoveredObjects.begin(), this->listOfHoveredObjects.end(), hoveredObject);
				this->listOfHoveredObjects.erase(objectIterator);
			}
		}
	}
}
