#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CMouseExitEvent.h"

CMouseExitEvent::CMouseExitEvent(const ex::Entity& exitObject)
	: exitObject(exitObject)
{ }

const ex::Entity& CMouseExitEvent::getExitObject() const
{
	return this->exitObject;
}
