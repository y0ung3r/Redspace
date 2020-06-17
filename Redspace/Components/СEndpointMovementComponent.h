#ifndef CENDPOINTMOVEMENTCOMPONENT_H
#define CENDPOINTMOVEMENTCOMPONENT_H

#include "CMovementComponent.h"

class ÑEndpointMovementComponent : public CMovementComponent
{
private:
	sf::Vector2f endpoint;

public:
	ÑEndpointMovementComponent(float speed, const sf::Vector2f& endpoint);

	const sf::Vector2f& getEndpoint();

	void setEndpoint(const sf::Vector2f& endpoint);
};

#endif