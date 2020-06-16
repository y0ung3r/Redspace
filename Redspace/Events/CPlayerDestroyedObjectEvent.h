#ifndef CPLAYERDESTROYEDOBJECTEVENT_H
#define CPLAYERDESTROYEDOBJECTEVENT_H

class CPlayerDestroyedObjectEvent
{
private:
	sf::Vector2f placeOfDestroy;

public:
	CPlayerDestroyedObjectEvent(const sf::Vector2f& placeOfDestroy);

	const sf::Vector2f& getPlaceOfDestroy() const;
};

#endif