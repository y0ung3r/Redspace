#include <random>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CDirectionMovementComponent.h"
#include "../Components/ÑEndpointMovementComponent.h"

#include "CMovementSystem.h"

CMovementSystem::CMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id mapId)
	: vectorHelper(vectorHelper), target(target), mapId(mapId)
{ }

void CMovementSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	time_t time = std::time(0);
	unsigned int seed = static_cast<unsigned int>(time);
	std::default_random_engine randomGenerator(seed);

	ex::Entity map = entities.get(this->mapId);
	ex::ComponentHandle<CRenderingComponent> mapRenderComponent = map.component<CRenderingComponent>();
	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();

	std::uniform_real_distribution<float> endpointDistributionX(mapGlobalBounds.left, mapGlobalBounds.width);
	std::uniform_real_distribution<float> endpointDistributionY(mapGlobalBounds.top, mapGlobalBounds.height);

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CMovementComponent*> entityBaseMovementComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityBaseMovementComponent))
	{
		CMovementComponent* entityMovementComponent = *entityBaseMovementComponent.get();

		sf::Vector2f entityPosition = entityRenderingComponent->getPosition();
		float entitySpeed = entityMovementComponent->getSpeed();

		sf::Vector2f direction;

		ObjectTypes entityTag = entityTagComponent->getTag();

		switch (entityTag)
		{

		case Player:
		{
			sf::Vector2f mousePosition = CGame::getMousePositionInCoords(this->target);
			float entityAngleRotate = vectorHelper.getAngleInDegrees(mousePosition, entityPosition);
			entityRenderingComponent->setRotation(entityAngleRotate);
			
			bool canMoveToTop = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			bool canMoveToLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
			bool canMoveToBottom = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
			bool canMoveToRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

			if (canMoveToTop)
			{
				direction.x = 0.0f;
				direction.y = -1.0f;
			}

			if (canMoveToLeft)
			{
				direction.x = -1.0f;
				direction.y = 0.0f;
			}

			if (canMoveToBottom)
			{
				direction.x = 0.0f;
				direction.y = 1.0f;
			}

			if (canMoveToRight)
			{
				direction.x = 1.0f;
				direction.y = 0.0f;
			}

			if (canMoveToTop && canMoveToLeft)
			{
				direction.x = -0.75f;
				direction.y = -0.75f;
			}

			if (canMoveToTop && canMoveToRight)
			{
				direction.x = 0.75f;
				direction.y = -0.75f;
			}

			if (canMoveToBottom && canMoveToLeft)
			{
				direction.x = -0.75f;
				direction.y = 0.75f;
			}

			if (canMoveToBottom && canMoveToRight)
			{
				direction.x = 0.75f;
				direction.y = 0.75f;
			}
		}
		break;

		case Enemy:
		{
			ÑEndpointMovementComponent* endpointMovementComponent = static_cast<ÑEndpointMovementComponent*>(entityMovementComponent);
			sf::Vector2f endpoint = endpointMovementComponent->getEndpoint();

			float entityAngleRotate = vectorHelper.getAngleInDegrees(endpoint, entityPosition);
			entityRenderingComponent->setRotation(entityAngleRotate);

			float distance = vectorHelper.getDistance(entityPosition, endpoint);

			if (distance >= 2.0f)
			{
				sf::Vector2f difference = endpoint - entityPosition;
				direction = vectorHelper.getOrt(difference);
			}
			else
			{
				endpoint.x = endpointDistributionX(randomGenerator);
				endpoint.y = endpointDistributionY(randomGenerator);

				endpointMovementComponent->setEndpoint(endpoint);
			}
		}
		break;

		case Bullet:
		{
			CDirectionMovementComponent* directionMovementComponent = static_cast<CDirectionMovementComponent*>(entityMovementComponent);
			direction = directionMovementComponent->getDirection();
		}
		break;

		}

		sf::Vector2f offset = entitySpeed * static_cast<float>(timeDelta) * direction;
		entityRenderingComponent->move(offset);
	}
}
