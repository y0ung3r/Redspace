#include "CPlayerSystem.h"

void CPlayerSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity player = entities.get(this->playerId);

	ex::ComponentHandle<CRenderComponent> playerRenderComponent = player.component<CRenderComponent>();
	ex::ComponentHandle<CMovementComponent> playerMovementComponent = player.component<CMovementComponent>();

	sf::Vector2i mousePositionInPixels = sf::Mouse::getPosition(this->target);
	sf::Vector2f mousePositionInCoords = this->target.mapPixelToCoords(mousePositionInPixels);
	sf::Vector2f playerPosition = playerRenderComponent->getPosition();
	
	float angleRotate = CVectorHelper::getAngleInDegrees(mousePositionInCoords, playerPosition);
	playerRenderComponent->setRotation(angleRotate);

	bool isMovingToTop = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool isMovingToLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool isMovingToBottom = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool isMovingToRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (isMovingToTop || isMovingToLeft || isMovingToBottom || isMovingToRight)
	{
		playerMovementComponent->addAcceleration(2.0f);
	}

	if (!isMovingToTop && !isMovingToLeft && !isMovingToBottom && !isMovingToRight)
	{
		playerMovementComponent->addAcceleration(-2.0f);
	}

	if (isMovingToTop)
	{
		playerMovementComponent->setDirection(0.0f, -1.0f);
	}

	if (isMovingToLeft)
	{
		playerMovementComponent->setDirection(-1.0f, 0.0f);
	}

	if (isMovingToBottom)
	{
		playerMovementComponent->setDirection(0.0f, 1.0f);
	}

	if (isMovingToRight)
	{
		playerMovementComponent->setDirection(1.0f, 0.0f);
	}

	if (isMovingToTop && isMovingToLeft)
	{
		playerMovementComponent->setDirection(-0.75f, -0.75f);
	}

	if (isMovingToTop && isMovingToRight)
	{
		playerMovementComponent->setDirection(0.75f, -0.75f);
	}

	if (isMovingToBottom && isMovingToLeft)
	{
		playerMovementComponent->setDirection(-0.75f, 0.75f);
	}

	if (isMovingToBottom && isMovingToRight)
	{
		playerMovementComponent->setDirection(0.75f, 0.75f);
	}

	sf::Vector2f direction = playerMovementComponent->getSpeed(timeDelta);
	playerRenderComponent->move(direction);

	/*bool isRequiredAcceleration = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

	if (isRequiredAcceleration)
	{
		playerMovementComponent->addAcceleration(2.0f);
	}

	sf::Vector2f mouseDirection = CVectorHelper::toNormalized(mousePositionInCoords);
	playerMovementComponent->setDirection(mouseDirection.x, mouseDirection.y);

	sf::Vector2f playerDirection = playerMovementComponent->getSpeed(timeDelta);
	playerRenderComponent->move(playerDirection);*/
}