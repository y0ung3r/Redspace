#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CLostVisibilityEvent.h"

CLostVisibilityEvent::CLostVisibilityEvent(const ex::Entity& lostObject)
	: lostObject(lostObject)
{ }

const ex::Entity& CLostVisibilityEvent::getLostObject() const
{
	return this->lostObject;
}
