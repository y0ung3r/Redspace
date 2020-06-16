#include <SFML/Graphics.hpp>

#include "CPlayerDestroyedObjectEvent.h"

CPlayerDestroyedObjectEvent::CPlayerDestroyedObjectEvent(const sf::Vector2f& placeOfDestroy)
	: placeOfDestroy(placeOfDestroy)
{ }

const sf::Vector2f& CPlayerDestroyedObjectEvent::getPlaceOfDestroy() const
{
	return this->placeOfDestroy;
}