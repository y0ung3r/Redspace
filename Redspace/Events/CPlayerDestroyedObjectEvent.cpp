#include <SFML/Graphics.hpp>

#include "../Enums/ObjectTypes.h"

#include "CPlayerDestroyedObjectEvent.h"

CPlayerDestroyedObjectEvent::CPlayerDestroyedObjectEvent(const sf::Vector2f& placeOfDestroy, ObjectTypes objectType)
	: placeOfDestroy(placeOfDestroy), objectType(objectType)
{ }

ObjectTypes CPlayerDestroyedObjectEvent::getObjectType() const
{
	return this->objectType;
}

const sf::Vector2f& CPlayerDestroyedObjectEvent::getPlaceOfDestroy() const
{
	return this->placeOfDestroy;
}