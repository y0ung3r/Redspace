#ifndef CSINGLEMOUSEBUTTONEVENT_H
#define CSINGLEMOUSEBUTTONEVENT_H

class CSingleMouseInputEvent
{
private:
	sf::Event::EventType type;

	sf::Event::MouseButtonEvent buttonInfo;

public:
	CSingleMouseInputEvent(const sf::Event::EventType& type, const sf::Event::MouseButtonEvent& buttonInfo);

	const sf::Event::EventType& getType() const;

	const sf::Event::MouseButtonEvent& getButtonInfo() const;
};

#endif