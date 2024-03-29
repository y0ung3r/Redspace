#include <SFML/Graphics.hpp>

#include "—EndpointMovementComponent.h"

—EndpointMovementComponent::—EndpointMovementComponent(float speed, const sf::Vector2f& endpoint)
	: CMovementComponent(speed)
{ 
	this->setEndpoint(endpoint);
}

const sf::Vector2f& —EndpointMovementComponent::getEndpoint()
{
	return this->endpoint;
}

void —EndpointMovementComponent::setEndpoint(const sf::Vector2f& endpoint)
{
	this->endpoint = endpoint;
}