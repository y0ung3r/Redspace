#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CShotFiredEvent.h"

CShotFiredEvent::CShotFiredEvent(const ex::Entity& objectWhichShot, const ex::Entity& bullet)
	: objectWhichShot(objectWhichShot), bullet(bullet)
{ }

const ex::Entity& CShotFiredEvent::getObjectWhichShot() const
{
	return this->objectWhichShot;
}

const ex::Entity& CShotFiredEvent::getBullet() const
{
	return this->bullet;
}
