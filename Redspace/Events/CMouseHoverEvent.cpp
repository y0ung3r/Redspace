#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CMouseHoverEvent.h"

CMouseHoverEvent::CMouseHoverEvent(const ex::Entity& hoveredObject)
	: hoveredObject(hoveredObject)
{ }

const ex::Entity& CMouseHoverEvent::getHoveredObject() const
{
	return this->hoveredObject;
}
