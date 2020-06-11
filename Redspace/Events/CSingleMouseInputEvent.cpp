#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CSingleMouseInputEvent.h"

CSingleMouseInputEvent::CSingleMouseInputEvent(const sf::Event::EventType& type, const sf::Event::MouseButtonEvent& buttonInfo)
	: type(type), buttonInfo(buttonInfo)
{ }

const sf::Event::EventType& CSingleMouseInputEvent::getType() const
{
	return this->type;
}

const sf::Event::MouseButtonEvent& CSingleMouseInputEvent::getButtonInfo() const
{
	return this->buttonInfo;
}
