#include <random>
#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CCollisionComponent.h"
#include "../Components/CRotationComponent.h"
#include "../Components/CMeteoriteComponent.h"
#include "../Components/CCircleBorderComponent.h"
#include "../Events/CCollisionEvent.h"

#include "CMeteoriteSystem.h"

CMeteoriteSystem::CMeteoriteSystem(sf::RenderWindow& target, ex::Entity::Id mapId, int count)
	: target(target), mapId(mapId), count(count)
{ }

void CMeteoriteSystem::configure(ex::EventManager& events)
{
	events.subscribe<CCollisionEvent>(*this);
}

void CMeteoriteSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	int counter = 0;

	time_t time = std::time(0);
	unsigned int seed = static_cast<unsigned int>(time);
	std::default_random_engine randomGenerator(seed);

	ex::Entity map = entities.get(this->mapId);
	ex::ComponentHandle<CRenderingComponent> mapRenderComponent = map.component<CRenderingComponent>();

	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();

	std::map<std::string, sf::Texture*> meteoritesTextures = CAssetsHelper::getInstance().getMeteoritesTextures();
	size_t meteoritesTexturesSize = meteoritesTextures.size();
	int meteoritesTexturesCount = static_cast<int>(meteoritesTexturesSize);

	ex::ComponentHandle<CRenderingComponent> renderComponent;
	ex::ComponentHandle<CRotationComponent> rotationComponent;
	ex::ComponentHandle<CCollisionComponent> collisionComponent;
	ex::ComponentHandle<CMeteoriteComponent> component;

	for (ex::Entity entity : entities.entities_with_components(renderComponent, rotationComponent, collisionComponent, component))
	{
		counter++;

		renderComponent->setColor(sf::Color::White);

		sf::FloatRect globalBounds = renderComponent->getGlobalBounds();

		renderComponent->rotate(static_cast<float>(timeDelta) * rotationComponent->rotationSpeed);
	}

	for (int i = 0; i < count - counter; i++)
	{
		ex::Entity meteorite = entities.create();

		CRenderingComponent meteoriteRenderComponent;

		std::uniform_int_distribution<int> textureNumberDistribution(0, meteoritesTexturesCount - 1);
		int textureNumber = textureNumberDistribution(randomGenerator);

		std::string meteoriteKey = "meteorite_" + std::to_string(textureNumber);
		sf::Texture* meteoriteTexture = meteoritesTextures[meteoriteKey];
		meteoriteRenderComponent.setTexture(*meteoriteTexture);

		sf::Vector2u meteoriteTextureSizeInPixels = meteoriteTexture->getSize();
		sf::Vector2f meteoriteTextureSizeInCoords = static_cast<sf::Vector2f>(meteoriteTextureSizeInPixels);

		sf::Vector2f meteoriteOrigin;
		meteoriteOrigin.x = meteoriteTextureSizeInCoords.x / 2.0f;
		meteoriteOrigin.y = meteoriteTextureSizeInCoords.y / 2.0f;
		meteoriteRenderComponent.setOrigin(meteoriteOrigin);

		sf::FloatRect mapSize = mapRenderComponent->getGlobalBounds();

		ex::ComponentHandle<CRenderingComponent> nearbyObjectRenderComponent;

		float positionX = 0.0f, positionY = 0.0f;
		
		while (positionX == 0.0f || positionY == 0.0f)
		{
			for (ex::Entity nearbyObject : entities.entities_with_components(nearbyObjectRenderComponent))
			{
				sf::FloatRect meteoriteGlobalBounds = meteoriteRenderComponent.getGlobalBounds();
				sf::FloatRect nearbyObjectGlobalBounds = nearbyObjectRenderComponent->getGlobalBounds();

				if (nearbyObjectGlobalBounds.intersects(meteoriteGlobalBounds))
				{
					std::uniform_real_distribution<float> positionDistributionX(mapSize.left, mapSize.width);
					positionX = positionDistributionX(randomGenerator);

					std::uniform_real_distribution<float> positionDistributionY(mapSize.top, mapSize.height);
					positionY = positionDistributionY(randomGenerator);

					sf::Vector2f meteoritePosition = sf::Vector2f(positionX, positionY);
					meteoriteRenderComponent.setPosition(meteoritePosition);
				}
			}
		}

		meteorite.assign<CRenderingComponent>(meteoriteRenderComponent);

		CCollisionComponent meteoriteCollisionComponent;
		meteorite.assign<CCollisionComponent>(meteoriteCollisionComponent);

		CRotationComponent meteoriteRotationComponent;

		std::uniform_real_distribution<float> rotationDistributionSpeed(-100.0f, 100.0f);
		meteoriteRotationComponent.rotationSpeed = rotationDistributionSpeed(randomGenerator);

		meteorite.assign<CRotationComponent>(meteoriteRotationComponent);

		CCircleBorderComponent circleBorderComponent;
		meteorite.assign<CCircleBorderComponent>(circleBorderComponent);

		CMeteoriteComponent meteoriteComponent;
		meteorite.assign<CMeteoriteComponent>(meteoriteComponent);
	}
}

void CMeteoriteSystem::receive(const CCollisionEvent& collisionEvent)
{ }