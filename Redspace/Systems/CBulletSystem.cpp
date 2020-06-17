#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"
#include "../Events/CCollisionEvent.h"
#include "../Events/CLostVisibilityEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CDirectionMovementComponent.h"
#include "../Components/CTagComponent.h"

#include "CBulletSystem.h"

CBulletSystem::CBulletSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CBulletSystem::configure(ex::EventManager& events)
{
	events.subscribe<CCollisionEvent>(*this);
	events.subscribe<CLostVisibilityEvent>(*this);
	events.subscribe<ex::EntityDestroyedEvent>(*this);
}

void CBulletSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	for (ex::Entity entity : this->listOfDestruction)
	{
		entity.destroy();
	}

	this->listOfDestruction.clear();
}

void CBulletSystem::receive(const CCollisionEvent& collisionEvent)
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

	bool canBeDestroyed = std::find(this->listOfDestruction.begin(), this->listOfDestruction.end(), bullet) == this->listOfDestruction.end();

	if (object && bullet && canBeDestroyed)
	{
		this->listOfDestruction.push_back(bullet);
	}
}

void CBulletSystem::receive(const CLostVisibilityEvent& lostVisibilityEvent)
{
	ex::Entity lostObject = lostVisibilityEvent.getLostObject();

	if (!lostObject)
	{
		return;
	}

	ex::ComponentHandle<CTagComponent> lostObjectTagComponent = lostObject.component<CTagComponent>();
	ObjectTypes lostObjectTag = lostObjectTagComponent->getTag();

	bool canBeDestroyed = std::find(this->listOfDestruction.begin(), this->listOfDestruction.end(), lostObject) == this->listOfDestruction.end();

	if (lostObjectTag == ObjectTypes::Bullet && canBeDestroyed)
	{
		this->listOfDestruction.push_back(lostObject);
	}
}

void CBulletSystem::receive(const ex::EntityDestroyedEvent& entityDestroyedEvent)
{
	// Перенести в отдельную систему?
	ex::Entity destroyedObject = entityDestroyedEvent.entity;

	if (!destroyedObject)
	{
		return;
	}

	ex::ComponentHandle<CTagComponent> destroyedObjectTagComponent = destroyedObject.component<CTagComponent>();
	ObjectTypes destroyedObjectTag = destroyedObjectTagComponent->getTag();

	if (destroyedObjectTag == ObjectTypes::Bullet)
	{
		// Отображать взрыв здесь?
	}
}