#include "CCollisionSystem.h"

void CCollisionSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderComponent> renderComponent;
	ex::ComponentHandle<CCollisionComponent> collisionComponent;

	for (ex::Entity entity : entities.entities_with_components(renderComponent, collisionComponent))
	{
		ex::Entity::Id entityId = entity.id();

		sf::FloatRect globalBounds = renderComponent->getGlobalBounds();

		ex::ComponentHandle<CRenderComponent> nearbyRenderComponent;
		ex::ComponentHandle<CCollisionComponent> nearbyCollisionComponent;

		for (ex::Entity nearbyEntity : entities.entities_with_components(nearbyRenderComponent, nearbyCollisionComponent))
		{
			ex::Entity::Id nearbyEntityId = nearbyEntity.id();

			if (entityId == nearbyEntityId)
			{
				continue;
			}

			sf::FloatRect nearbyGlobalBounds = nearbyRenderComponent->getGlobalBounds();

			if (globalBounds.intersects(nearbyGlobalBounds))
			{
				events.emit<CCollisionEvent>(entity, nearbyEntity);
			}
		}
	}
}