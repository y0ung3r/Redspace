#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"
#include "../Events/CCollisionEvent.h"
#include "../Events/CLostVisibilityEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CBulletMovementComponent.h"
#include "../Components/CTagComponent.h"

#include "CBulletSystem.h"

CBulletSystem::CBulletSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CBulletSystem::configure(ex::EventManager& events)
{
	events.subscribe<CCollisionEvent>(*this);
	events.subscribe<CLostVisibilityEvent>(*this);
}

void CBulletSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{ }

void CBulletSystem::receive(const CCollisionEvent& collisionEvent)
{
	ex::Entity firstEntity = collisionEvent.getFirstEntity();
	ex::ComponentHandle<CTagComponent> firstEntityTagComponent = firstEntity.component<CTagComponent>();
	ObjectTypes firstEntityType = firstEntityTagComponent->getTag();

	ex::Entity secondEntity = collisionEvent.getSecondEntity();
	ex::ComponentHandle<CTagComponent> secondEntityTagComponent = secondEntity.component<CTagComponent>();
	ObjectTypes secondEntityType = secondEntityTagComponent->getTag();

	ex::Entity object, bullet;
}

void CBulletSystem::receive(const CLostVisibilityEvent& lostVisibilityEvent)
{
	ex::Entity lostObject = lostVisibilityEvent.getLostObject();

	ex::ComponentHandle<CTagComponent> lostObjectTagComponent = lostObject.component<CTagComponent>();
	ObjectTypes lostObjectTag = lostObjectTagComponent->getTag();

	if (lostObjectTag == ObjectTypes::Bullet)
	{
		lostObject.destroy();
	}
}
