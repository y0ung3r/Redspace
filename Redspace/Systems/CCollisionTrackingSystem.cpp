#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"
#include "../Events/CCollisionEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"

#include "CCollisionTrackingSystem.h"

CCollisionTrackingSystem::CCollisionTrackingSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CCollisionTrackingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent))
	{
		ex::Entity::Id entityId = entity.id();

		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag != ObjectTypes::Map && entityTag != ObjectTypes::Camera)
		{
			sf::FloatRect entityGlobalBounds = entityRenderingComponent->getGlobalBounds();

			ex::ComponentHandle<CRenderingComponent> nearbyEntityRenderingComponent;
			ex::ComponentHandle<CTagComponent> nearbyEntityTagComponent;

			for (ex::Entity nearbyEntity : entities.entities_with_components(nearbyEntityRenderingComponent, nearbyEntityTagComponent))
			{
				ex::Entity::Id nearbyEntityId = nearbyEntity.id();

				ObjectTypes nearbyEntityTag = nearbyEntityTagComponent->getTag();

				if (entityId != nearbyEntityId && nearbyEntityTag != ObjectTypes::Map && nearbyEntityTag != ObjectTypes::Camera)
				{
					sf::FloatRect nearbyEntityGlobalBounds = nearbyEntityRenderingComponent->getGlobalBounds();

					if (entityGlobalBounds.intersects(nearbyEntityGlobalBounds))
					{
						events.emit<CCollisionEvent>(entity, nearbyEntity);
					}
				}
			}
		}
	}
}