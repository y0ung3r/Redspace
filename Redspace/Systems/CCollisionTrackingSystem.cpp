#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"
#include "../Events/CCollisionEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Extensions/Collision.h"

#include "CCollisionTrackingSystem.h"

CCollisionTrackingSystem::CCollisionTrackingSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CCollisionTrackingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;

	int entityIndex = 0;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent))
	{
		ex::Entity::Id entityId = entity.id();

		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag != ObjectTypes::Map && entityTag != ObjectTypes::Camera)
		{
			ex::ComponentHandle<CRenderingComponent> nearbyEntityRenderingComponent;
			ex::ComponentHandle<CTagComponent> nearbyEntityTagComponent;

			int nearbyEntityIndex = 0;

			for (ex::Entity nearbyEntity : entities.entities_with_components(nearbyEntityRenderingComponent, nearbyEntityTagComponent))
			{
				if (entityIndex <= nearbyEntityIndex)
				{
					ex::Entity::Id nearbyEntityId = nearbyEntity.id();

					ObjectTypes nearbyEntityTag = nearbyEntityTagComponent->getTag();

					if (entity && nearbyEntity && entityId != nearbyEntityId && nearbyEntityTag != ObjectTypes::Map && nearbyEntityTag != ObjectTypes::Camera)
					{
						sf::Sprite entitySprite = *entityRenderingComponent.get();
						sf::Sprite nearbyEntitySprite = *nearbyEntityRenderingComponent.get();

						if (Collision::BoundingBoxTest(entitySprite, nearbyEntitySprite))
						{
							events.emit<CCollisionEvent>(entity, entityTag, nearbyEntity, nearbyEntityTag);
						}
					}
				}

				nearbyEntityIndex++;
			}

			entityIndex++;
		}
	}
}