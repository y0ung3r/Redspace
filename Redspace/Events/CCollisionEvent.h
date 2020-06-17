#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

/* Класс, хранящий в себе информацию о столкновении двух объектов */
class CCollisionEvent
{
private:
	/* Первый объект, столкнувшийся со вторым */
	ex::Entity entity;

	ObjectTypes entityType;

	/* Второй объект, столкнувшийся с первым */
	ex::Entity nearbyEntity;

	ObjectTypes nearbyEntityType;

public:
	/* Базовый конструктор */
	CCollisionEvent(const ex::Entity& entity, ObjectTypes entityType, const ex::Entity& nearbyEntity, ObjectTypes nearbyEntityType);

	const ex::Entity& getEntity() const;

	ObjectTypes getEntityType() const;

	const ex::Entity& getNearbyEntity() const;

	ObjectTypes getNearbyEntityType() const;
};

#endif