#include <random>
#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Interfaces/IObjectFactory.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"

#include "CMeteoriteSystem.h"

CMeteoriteSystem::CMeteoriteSystem(IObjectFactory& meteoriteFactory, CGame& game, sf::RenderWindow& target, int maxCount)
	: meteoriteFactory(meteoriteFactory), game(game), target(target), maxCount(maxCount)
{ }

void CMeteoriteSystem::configure(ex::EventManager & events)
{
	events.subscribe<ex::EntityDestroyedEvent>(*this);
}

void CMeteoriteSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	int count = 0;

	time_t time = std::time(0);
	unsigned int seed = static_cast<unsigned int>(time);
	std::default_random_engine randomGenerator(seed);

	ex::Entity::Id mapId = this->game.getMapId();
	ex::Entity map = entities.get(mapId);
	ex::ComponentHandle<CRenderingComponent> mapRenderComponent = map.component<CRenderingComponent>();

	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();

	size_t meteoritesTexturesSize = CAssetsHelper::getInstance().getMeteoritesTextures().size();
	int meteoritesTexturesCount = static_cast<int>(meteoritesTexturesSize);

	ex::ComponentHandle<CRenderingComponent> renderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;

	for (ex::Entity entity : entities.entities_with_components(renderingComponent, entityTagComponent))
	{
		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag == ObjectTypes::Meteorite)
		{
			count++;

			renderingComponent->rotate(static_cast<float>(timeDelta) * 50.0f);
		}
	}

	for (int i = 0; i < this->maxCount - count; i++)
	{
		std::uniform_int_distribution<int> textureNumberDistribution(0, meteoritesTexturesCount - 1);
		int textureNumber = textureNumberDistribution(randomGenerator);
		std::string meteoriteKey = "meteorite_" + std::to_string(textureNumber);

		std::uniform_real_distribution<float> positionDistributionX(mapGlobalBounds.left, mapGlobalBounds.width);
		float positionX = positionDistributionX(randomGenerator);

		std::uniform_real_distribution<float> positionDistributionY(mapGlobalBounds.top, mapGlobalBounds.height);
		float positionY = positionDistributionY(randomGenerator);

		sf::Vector2f entityPosition = sf::Vector2f(positionX, positionY);
		meteoriteFactory.create(meteoriteKey, entityPosition);
	}
}

void CMeteoriteSystem::receive(const ex::EntityDestroyedEvent& entityDestroyedEvent)
{
	ex::Entity destroyedObject = entityDestroyedEvent.entity;

	if (!destroyedObject)
	{
		return;
	}

	ex::ComponentHandle<CTagComponent> destroyedObjectTagComponent = destroyedObject.component<CTagComponent>();
	ObjectTypes destroyedObjectTag = destroyedObjectTagComponent->getTag();

	if (destroyedObjectTag == ObjectTypes::Meteorite)
	{
		this->maxCount--;
	}
}
