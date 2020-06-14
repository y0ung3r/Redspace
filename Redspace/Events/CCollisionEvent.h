#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

/* �����, �������� � ���� ���������� � ������������ ���� �������� */
class CCollisionEvent
{
private:
	/* ������ ������, ������������� �� ������ */
	ex::Entity entity;

	ObjectTypes entityType;

	/* ������ ������, ������������� � ������ */
	ex::Entity nearbyEntity;

	ObjectTypes nearbyEntityType;

public:
	/* ������� ����������� */
	CCollisionEvent(const ex::Entity& entity, ObjectTypes entityType, const ex::Entity& nearbyEntity, ObjectTypes nearbyEntityType);

	const ex::Entity& getEntity() const;

	ObjectTypes getEntityType() const;

	const ex::Entity& getNearbyEntity() const;

	ObjectTypes getNearbyEntityType() const;
};

#endif