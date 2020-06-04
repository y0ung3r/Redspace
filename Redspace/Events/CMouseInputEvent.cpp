#include <SFML/Graphics.hpp>

#include "CMouseInputEvent.h"

CMouseInputEvent::CMouseInputEvent(const sf::Event::MouseButtonEvent& mouseInputEvent)
	: instance(mouseInputEvent)
{ }