#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CCollisionEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CHealthComponent.h"
#include "../Events/CShotFiredEvent.h"
#include "../Events/CPlayerDestroyedObjectEvent.h"

#include "CHealthSystem.h"

CHealthSystem::CHealthSystem(CGame& game, sf::RenderWindow& target)
	: game(game), target(target)
{ }

void CHealthSystem::configure(ex::EventManager& events)
{
	events.subscribe<CShotFiredEvent>(*this);
	events.subscribe<CCollisionEvent>(*this);
}

void CHealthSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{ 
	for (DestroyInfo destroyInfo : this->destroyInfoList)
	{
		if (destroyInfo.destroyedByPlayer)
		{
			events.emit<CPlayerDestroyedObjectEvent>(destroyInfo.placeOfDestroy);
		}

		destroyInfo.object.destroy();
	}

	this->destroyInfoList.clear();
}

void CHealthSystem::receive(const CShotFiredEvent& shotFiredEvent)
{
	ex::Entity::Id playerId = this->game.getPlayerId();
	ex::Entity::Id objectId = shotFiredEvent.getObjectWhichShot().id();
	
	if (playerId == objectId)
	{
		ex::Entity bullet = shotFiredEvent.getBullet();
		this->playerBulletList.push_back(bullet);
	}
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
		ex::ComponentHandle<CRenderingComponent> objectRenderingComponent = object.component<CRenderingComponent>();
		ex::ComponentHandle<CHealthComponent> objectHealthComponent = object.component<CHealthComponent>();

		float health = objectHealthComponent->getHealth();

		if (!objectHealthComponent->isDead())
		{
			health -= 15.25f; // ¬вести переменную дл€ подсчЄта урона
			objectHealthComponent->setHealth(health);

			bool canBeDestroyed = std::find(this->destroyInfoList.begin(), this->destroyInfoList.end(), object) == this->destroyInfoList.end();

			if (health <= 0.0f && canBeDestroyed)
			{
				DestroyInfo destroyInfo;

				destroyInfo.object = object;
				destroyInfo.bullet = bullet;
				destroyInfo.placeOfDestroy = objectRenderingComponent->getPosition();

				for (ex::Entity playerBullet : this->playerBulletList)
				{
					ex::Entity::Id playerBulletId = playerBullet.id();
					ex::Entity::Id bulletId = destroyInfo.bullet.id();

					if (playerBulletId == bulletId)
					{
						destroyInfo.destroyedByPlayer = true;
					}
				}
				
				this->playerBulletList.clear();
				this->destroyInfoList.push_back(destroyInfo);
			}
		}
	}
}
