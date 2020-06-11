#include <SFML/Graphics.hpp>

#include "CBulletMovementComponent.h"

CBulletMovementComponent::CBulletMovementComponent(float speed, const sf::Vector2f& direction)
	: CMovementComponent(speed), direction(direction)
{ }

const sf::Vector2f& CBulletMovementComponent::getDirection()
{
	return this->direction;
}
