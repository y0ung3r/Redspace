#include <SFML/Graphics.hpp>

#include "ÑEndpointMovementComponent.h"

ÑEndpointMovementComponent::ÑEndpointMovementComponent(float speed, const sf::Vector2f& endpoint)
	: CMovementComponent(speed)
{ 
	this->setEndpoint(endpoint);
}

bool ÑEndpointMovementComponent::canMove()
{
	return this->isCanMove;
}

const sf::Vector2f& ÑEndpointMovementComponent::getEndpoint()
{
	return this->endpoint;
}

void ÑEndpointMovementComponent::setEndpoint(const sf::Vector2f& endpoint)
{
	this->endpoint = endpoint;
	this->isCanMove = true;
}