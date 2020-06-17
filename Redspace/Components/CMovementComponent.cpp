#include "CMovementComponent.h"

CMovementComponent::CMovementComponent(float speed)
	: speed(speed)
{ }

float CMovementComponent::getSpeed()
{
	return this->speed;
}

void CMovementComponent::setSpeed(float speed)
{
	this->speed = speed;
}