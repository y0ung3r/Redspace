#include "CMovementComponent.h"

CMovementComponent::CMovementComponent(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
	this->speed = 150.0f;
	this->direction = sf::Vector2f(1.0f, 1.0f);
}

const sf::Vector2f& CMovementComponent::getSpeed(ex::TimeDelta timeDelta)
{
	return sf::Vector2f(this->direction.x, this->direction.y) * this->speed * static_cast<float>(timeDelta);
}

void CMovementComponent::setDirection(float x, float y)
{
	this->direction.x = x;
	this->direction.y = y;
}

void CMovementComponent::addAcceleration(float acceleration)
{
	if (this->speed <= this->maxSpeed)
	{
		this->speed += acceleration;
	}
}