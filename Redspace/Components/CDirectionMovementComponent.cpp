#include <SFML/Graphics.hpp>

#include "CDirectionMovementComponent.h"

CDirectionMovementComponent::CDirectionMovementComponent(float speed, const sf::Vector2f& direction)
	: CMovementComponent(speed), direction(direction)
{ }

const sf::Vector2f& CDirectionMovementComponent::getDirection()
{
	return this->direction;
}
