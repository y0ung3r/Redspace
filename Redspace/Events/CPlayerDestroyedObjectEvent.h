#ifndef CPLAYERDESTROYEDOBJECTEVENT_H
#define CPLAYERDESTROYEDOBJECTEVENT_H

class CPlayerDestroyedObjectEvent
{
private:
	ObjectTypes objectType;

	sf::Vector2f placeOfDestroy;

public:
	CPlayerDestroyedObjectEvent(const sf::Vector2f& placeOfDestroy, ObjectTypes objectType);

	ObjectTypes getObjectType() const;

	const sf::Vector2f& getPlaceOfDestroy() const;
};

#endif