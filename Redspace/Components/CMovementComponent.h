#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

class CMovementComponent
{
private:
	float speed;

public:
	CMovementComponent(float speed);

	float getSpeed();

	void setSpeed(float speed);
};

#endif