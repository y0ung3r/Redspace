#ifndef CDIRECTIONMOVEMENTCOMPONENT_H
#define CDIRECTIONMOVEMENTCOMPONENT_H

#include "CMovementComponent.h"

class CDirectionMovementComponent : public CMovementComponent
{
private:
	sf::Vector2f direction;

public:
	CDirectionMovementComponent(float speed, const sf::Vector2f& direction);

	const sf::Vector2f& getDirection();
};

#endif