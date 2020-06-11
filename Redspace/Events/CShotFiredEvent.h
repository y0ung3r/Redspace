#ifndef CSHOTFIREDEVENT_H
#define CSHOTFIREDEVENT_H

class CShotFiredEvent
{
private:
	ex::Entity objectWhichShot;

public:
	CShotFiredEvent(const ex::Entity& objectWhichShot);

	const ex::Entity& getObjectWhichShot() const;
};

#endif