#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

#include <entityx/entityx.h>

namespace ex = entityx;

/* �����, �������� � ���� ���������� � ������������ ���� �������� */
class CCollisionEvent
{
private:
	/* ������ ������, ������������� �� ������ */
	ex::Entity firstEntity;

	/* ������ ������, ������������� � ������ */
	ex::Entity secondEntity;

public:
	/* ������� ����������� */
	CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity)
		: firstEntity(firstEntity), secondEntity(secondEntity)
	{ }

	/* ���������� ������ ������ */
	const ex::Entity& getFirstEntity() const;

	/* ���������� ������ ������ */
	const ex::Entity& getSecondEntity() const;
};

#endif