#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"

#include "CCollisionEvent.h"

CCollisionEvent::CCollisionEvent(const ex::Entity& entity, ObjectTypes entityType, const ex::Entity& nearbyEntity, ObjectTypes nearbyEntityType)
	: entity(entity), entityType(entityType), nearbyEntity(nearbyEntity), nearbyEntityType(nearbyEntityType)
{ }

const ex::Entity& CCollisionEvent::getEntity() const
{
	return this->entity;
}

ObjectTypes CCollisionEvent::getEntityType() const
{
	return this->entityType;
}

const ex::Entity& CCollisionEvent::getNearbyEntity() const
{
	return this->nearbyEntity;
}

ObjectTypes CCollisionEvent::getNearbyEntityType() const
{
	return this->nearbyEntityType;
}
