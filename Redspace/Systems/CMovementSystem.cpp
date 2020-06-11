#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CBulletMovementComponent.h"

#include "CMovementSystem.h"

CMovementSystem::CMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target)
	: vectorHelper(vectorHelper), target(target)
{ }

void CMovementSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
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

		}
		break;

		case Bullet:
		{
			CBulletMovementComponent* bulletMovementComponent = static_cast<CBulletMovementComponent*>(entityMovementComponent);
			entitySpeed = bulletMovementComponent->getSpeed();
			direction = bulletMovementComponent->getDirection();
		}
		break;

		}

		sf::Vector2f endpoint = entitySpeed * static_cast<float>(timeDelta) * direction;
		entityRenderingComponent->move(endpoint);
	}
}
