#ifndef CMOUSEINPUTEVENT_H
#define CMOUSEINPUTEVENT_H

class CMouseInputEvent
{
public:
	sf::Event::MouseButtonEvent instance;
	CMouseInputEvent(const sf::Event::MouseButtonEvent& mouseInputEvent);
};

#endif