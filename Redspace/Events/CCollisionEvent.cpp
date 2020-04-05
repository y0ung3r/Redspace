#include <entityx/entityx.h>

namespace ex = entityx;

#include "CCollisionEvent.h"

CCollisionEvent::CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity) 
	: firstEntity(firstEntity), secondEntity(secondEntity)
{ }

const ex::Entity& CCollisionEvent::getFirstEntity() const
{
	return this->firstEntity;
}

const ex::Entity& CCollisionEvent::getSecondEntity() const
{
	return this->secondEntity;
}