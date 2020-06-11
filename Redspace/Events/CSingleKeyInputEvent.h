#ifndef CSINGLEKEYINPUTEVENT_H
#define CSINGLEKEYINPUTEVENT_H

class CSingleKeyInputEvent
{
private:
	sf::Event::EventType type;

	sf::Event::KeyEvent keyInfo;

public:
	CSingleKeyInputEvent(const sf::Event::EventType& type, const sf::Event::KeyEvent& keyInfo);

	const sf::Event::EventType& getType() const;

	const sf::Event::KeyEvent& getKeyInfo() const;
};

#endif