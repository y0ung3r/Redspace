#ifndef CSHOTFIREDEVENT_H
#define CSHOTFIREDEVENT_H

class CShotFiredEvent
{
private:
	ex::Entity objectWhichShot;

	ex::Entity bullet;

public:
	CShotFiredEvent(const ex::Entity& objectWhichShot, const ex::Entity& bullet);

	const ex::Entity& getObjectWhichShot() const;

	const ex::Entity& getBullet() const;
};

#endif