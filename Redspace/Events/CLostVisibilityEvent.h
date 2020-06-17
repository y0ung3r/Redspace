#ifndef CLOSTVISIBILITYEVENT_H
#define CLOSTVISIBILITYEVENT_H

class CLostVisibilityEvent
{
private:
	ex::Entity lostObject;

public:
	CLostVisibilityEvent(const ex::Entity& lostObject);

	const ex::Entity& getLostObject() const;
};

#endif