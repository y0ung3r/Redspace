#include <random>
#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Events/CCollisionEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CCollisionComponent.h"
#include "../Components/CRotationComponent.h"
#include "../Components/CEnemyComponent.h"
#include "../Components/CCircleBorderComponent.h"
#include "../Components/CPlayerComponent.h"

#include "CEnemySystem.h"

CEnemySystem::CEnemySystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id mapId, int count)
	: vectorHelper(vectorHelper), target(target), mapId(mapId), count(count)
{ }

void CEnemySystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	int counter = 0;

	time_t time = std::time(0);
	unsigned int seed = static_cast<unsigned int>(time);
	std::default_random_engine randomGenerator(seed);

	ex::Entity map = entities.get(this->mapId);
	ex::ComponentHandle<CRenderingComponent> mapRenderComponent = map.component<CRenderingComponent>();

	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();
	sf::FloatRect mapSize = mapRenderComponent->getGlobalBounds();

	std::map<std::string, sf::Texture*> enemiesTextures = CAssetsHelper::getInstance().getEnemiesTextures();
	size_t enemiesTexturesSize = enemiesTextures.size();
	int enemiesTexturesCount = static_cast<int>(enemiesTexturesSize);

	ex::ComponentHandle<CRenderingComponent> renderingComponent;
	ex::ComponentHandle<CMovementComponent> movementComponent;
	ex::ComponentHandle<CRotationComponent> rotationComponent;
	ex::ComponentHandle<CCollisionComponent> collisionComponent;
	ex::ComponentHandle<CEnemyComponent> component;

	for (ex::Entity entity : entities.entities_with_components(renderingComponent, movementComponent, rotationComponent, collisionComponent, component))
	{
		counter++;

		sf::Vector2f enemyPosition = renderingComponent->getPosition();

		{
			sf::Vector2f difference = movementComponent->moveTo - enemyPosition;
			sf::Vector2f direction = vectorHelper.getOrt(difference);

			float distance = vectorHelper.getLength(difference);

			if (distance >= 3.0f)
			{
				renderingComponent->move(movementComponent->speed * static_cast<float>(timeDelta) * direction);
			}
			else
			{
				std::uniform_real_distribution<float> positionDistributionX(mapSize.left, mapSize.width);
				float positionX = positionDistributionX(randomGenerator);

				std::uniform_real_distribution<float> positionDistributionY(mapSize.top, mapSize.height);
				float positionY = positionDistributionY(randomGenerator);

				movementComponent->moveTo = sf::Vector2f(positionX, positionY);
				rotationComponent->rotateTo = movementComponent->moveTo;
			}
		}

		{
			float enemyAngleRotate = renderingComponent->getRotation();
			float destinationAngleRotate = vectorHelper.getAngleInDegrees(rotationComponent->rotateTo, enemyPosition);
			renderingComponent->setRotation(destinationAngleRotate);
		}
	}

	for (int i = 0; i < count - counter; i++)
	{
		ex::Entity enemy = entities.create();

		CRenderingComponent enemyRenderComponent;

		sf::Texture* enemyTexture = enemiesTextures["enemy"];
		enemyRenderComponent.setTexture(*enemyTexture);

		sf::Vector2u enemyTextureSizeInPixels = enemyTexture->getSize();
		sf::Vector2f enemyTextureSizeInCoords = static_cast<sf::Vector2f>(enemyTextureSizeInPixels);

		sf::Vector2f enemyOrigin;
		enemyOrigin.x = enemyTextureSizeInCoords.x / 2.0f;
		enemyOrigin.y = enemyTextureSizeInCoords.y / 2.0f;
		enemyRenderComponent.setOrigin(enemyOrigin);

		ex::ComponentHandle<CRenderingComponent> nearbyObjectRenderComponent;

		float positionX = 0.0f, positionY = 0.0f;

		while (positionX == 0.0f || positionY == 0.0f)
		{
			for (ex::Entity nearbyObject : entities.entities_with_components(nearbyObjectRenderComponent))
			{
				if (nearbyObject.id() != enemy.id())
				{
					sf::FloatRect enemyGlobalBounds = enemyRenderComponent.getGlobalBounds();
					sf::FloatRect nearbyObjectGlobalBounds = nearbyObjectRenderComponent->getGlobalBounds();

					if (nearbyObjectGlobalBounds.intersects(enemyGlobalBounds))
					{
						std::uniform_real_distribution<float> positionDistributionX(mapSize.left, mapSize.width);
						positionX = positionDistributionX(randomGenerator);

						std::uniform_real_distribution<float> positionDistributionY(mapSize.top, mapSize.height);
						positionY = positionDistributionY(randomGenerator);

						sf::Vector2f enemyPosition = sf::Vector2f(positionX, positionY);
						enemyRenderComponent.setPosition(enemyPosition);
					}
				}
			}
		}

		enemy.assign<CRenderingComponent>(enemyRenderComponent);

		CCollisionComponent enemyCollisionComponent;
		enemy.assign<CCollisionComponent>(enemyCollisionComponent);

		CRotationComponent enemyRotationComponent;

		std::uniform_real_distribution<float> rotationDistributionSpeed(-100.0f, 100.0f);
		enemyRotationComponent.rotationSpeed = rotationDistributionSpeed(randomGenerator);

		enemy.assign<CRotationComponent>(enemyRotationComponent);

		CMovementComponent enemyMovementComponent;
		enemyMovementComponent.moveTo = sf::Vector2f(positionX, positionY);
		enemy.assign<CMovementComponent>(enemyMovementComponent);

		CCircleBorderComponent circleBorderComponent;
		enemy.assign<CCircleBorderComponent>(circleBorderComponent);

		CEnemyComponent enemyComponent;
		enemy.assign<CEnemyComponent>(enemyComponent);
	}
}