#include <entityx/entityx.h>

namespace ex = entityx;

#include "CCollisionEvent.h"

CCollisionEvent::CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity) 
	: firstEntity(firstEntity), secondEntity(secondEntity)
{ }