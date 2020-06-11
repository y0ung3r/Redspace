#ifndef CBULLETMOVEMENTCOMPONENT_H
#define CBULLETMOVEMENTCOMPONENT_H

#include "CMovementComponent.h"

class CBulletMovementComponent : public CMovementComponent
{
private:
	sf::Vector2f direction;

public:
	CBulletMovementComponent(float speed, const sf::Vector2f& direction);

	const sf::Vector2f& getDirection();
};

#endif