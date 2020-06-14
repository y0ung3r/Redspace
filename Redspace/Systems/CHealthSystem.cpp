#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"
#include "../Events/CCollisionEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CHealthComponent.h"

#include "CHealthSystem.h"

CHealthSystem::CHealthSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CHealthSystem::configure(ex::EventManager& events)
{
	events.subscribe<CCollisionEvent>(*this);
}

void CHealthSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{ 
	for (ex::Entity entity : this->listOfDestruction)
	{
		entity.destroy();
	}

	this->listOfDestruction.clear();
}

void CHealthSystem::receive(const CCollisionEvent& collisionEvent)
{
	ObjectTypes entityType = collisionEvent.getEntityType();
	ObjectTypes nearbyEntityType = collisionEvent.getNearbyEntityType();

	ex::Entity object, bullet;

	if (entityType != ObjectTypes::Bullet && nearbyEntityType == ObjectTypes::Bullet)
	{
		object = collisionEvent.getEntity();
		bullet = collisionEvent.getNearbyEntity();
	}
	else if (entityType == ObjectTypes::Bullet && nearbyEntityType != ObjectTypes::Bullet)
	{
		object = collisionEvent.getNearbyEntity();
		bullet = collisionEvent.getEntity();
	}

	if (object && object.has_component<CHealthComponent>() && bullet)
	{
		ex::ComponentHandle<CHealthComponent> objectHealthComponent = object.component<CHealthComponent>();

		float health = objectHealthComponent->getHealth();

		if (!objectHealthComponent->isDead())
		{
			health -= 15.0f; // ¬вести переменную дл€ подсчЄта урона
			objectHealthComponent->setHealth(health);

			bool canBeDestroyed = std::find(this->listOfDestruction.begin(), this->listOfDestruction.end(), object) == this->listOfDestruction.end();

			if (health <= 0.0f && canBeDestroyed)
			{
				this->listOfDestruction.push_back(object);
			}
		}
	}
}
