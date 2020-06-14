#include <random>
#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Interfaces/IObjectFactory.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"

#include "CEnemySystem.h"

CEnemySystem::CEnemySystem(IObjectFactory& enemyFactory, sf::RenderWindow& target, ex::Entity::Id mapId, int maxCount)
	: enemyFactory(enemyFactory), target(target), mapId(mapId), maxCount(maxCount)
{ }

void CEnemySystem::configure(ex::EventManager & events)
{
	events.subscribe<ex::EntityDestroyedEvent>(*this);
}

void CEnemySystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	int count = 0;

	time_t time = std::time(0);
	unsigned int seed = static_cast<unsigned int>(time);
	std::default_random_engine randomGenerator(seed);

	ex::Entity map = entities.get(this->mapId);
	ex::ComponentHandle<CRenderingComponent> mapRenderComponent = map.component<CRenderingComponent>();
	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CMovementComponent*> entityBaseMovementComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityBaseMovementComponent))
	{
		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag == ObjectTypes::Enemy)
		{
			count++;
		}
	}

	for (int i = 0; i < this->maxCount - count; i++)
	{
		std::uniform_real_distribution<float> positionDistributionX(mapGlobalBounds.left, mapGlobalBounds.width);
		float positionX = positionDistributionX(randomGenerator);

		std::uniform_real_distribution<float> positionDistributionY(mapGlobalBounds.top, mapGlobalBounds.height);
		float positionY = positionDistributionY(randomGenerator);

		sf::Vector2f entityPosition = sf::Vector2f(positionX, positionY);
		enemyFactory.create("enemy", entityPosition);
	}
}

void CEnemySystem::receive(const ex::EntityDestroyedEvent& entityDestroyedEvent)
{
	ex::Entity destroyedObject = entityDestroyedEvent.entity;

	if (!destroyedObject)
	{
		return;
	}

	ex::ComponentHandle<CTagComponent> destroyedObjectTagComponent = destroyedObject.component<CTagComponent>();
	ObjectTypes destroyedObjectTag = destroyedObjectTagComponent->getTag();

	if (destroyedObjectTag == ObjectTypes::Enemy)
	{
		this->maxCount--;
	}
}
