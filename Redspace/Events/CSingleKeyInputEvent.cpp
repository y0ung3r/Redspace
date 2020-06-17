#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "CSingleKeyInputEvent.h"

CSingleKeyInputEvent::CSingleKeyInputEvent(const sf::Event::EventType& type, const sf::Event::KeyEvent& keyInfo)
	: type(type), keyInfo(keyInfo)
{ }

const sf::Event::EventType& CSingleKeyInputEvent::getType() const
{
	return this->type;
}

const sf::Event::KeyEvent& CSingleKeyInputEvent::getKeyInfo() const
{
	return this->keyInfo;
}
