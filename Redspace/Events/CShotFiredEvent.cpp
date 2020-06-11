#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CShotFiredEvent.h"

CShotFiredEvent::CShotFiredEvent(const ex::Entity& objectWhichShot)
	: objectWhichShot(objectWhichShot)
{ }

const ex::Entity& CShotFiredEvent::getObjectWhichShot() const
{
	return this->objectWhichShot;
}
