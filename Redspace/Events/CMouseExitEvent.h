#ifndef CMOUSEEXITEVENT_H
#define CMOUSEEXITEVENT_H

class CMouseExitEvent
{
private:
	ex::Entity exitObject;

public:
	CMouseExitEvent(const ex::Entity& exitObject);

	const ex::Entity& getExitObject() const;
};

#endif