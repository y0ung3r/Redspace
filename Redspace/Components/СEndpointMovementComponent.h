#ifndef CENDPOINTMOVEMENTCOMPONENT_H
#define CENDPOINTMOVEMENTCOMPONENT_H

#include "CMovementComponent.h"

class �EndpointMovementComponent : public CMovementComponent
{
private:
	sf::Vector2f endpoint;

public:
	�EndpointMovementComponent(float speed, const sf::Vector2f& endpoint);

	const sf::Vector2f& getEndpoint();

	void setEndpoint(const sf::Vector2f& endpoint);
};

#endif