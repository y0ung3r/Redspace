#include "CMovementComponent.h"

const sf::Vector2f& CMovementComponent::getSpeed(ex::TimeDelta timeDelta)
{
	return sf::Vector2f(this->direction.x, this->direction.y) * this->speed * static_cast<float>(timeDelta);
}

const sf::Vector2f& CMovementComponent::getDirection()
{
	return this->direction;
}

void CMovementComponent::setDirection(float x, float y)
{
	this->direction.x = x;
	this->direction.y = y;
}

void CMovementComponent::addAcceleration(float acceleration)
{
	if (this->speed > this->maxSpeed && acceleration > 0)
	{
		return;
	}

	if (this->speed <= 0 && acceleration < 0)
	{
		return;
	}

	this->speed += acceleration;
}