#include "CCollisionEvent.h"

const ex::Entity& CCollisionEvent::getFirstEntity() const
{
	return this->firstEntity;
}

const ex::Entity& CCollisionEvent::getSecondEntity() const
{
	return this->secondEntity;
}