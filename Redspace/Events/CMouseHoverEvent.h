#ifndef CMOUSEHOVEREVENT_H
#define CMOUSEHOVEREVENT_H

class CMouseHoverEvent
{
private:
	ex::Entity hoveredObject;

public:
	CMouseHoverEvent(const ex::Entity& hoveredObject);

	const ex::Entity& getHoveredObject() const;
};

#endif