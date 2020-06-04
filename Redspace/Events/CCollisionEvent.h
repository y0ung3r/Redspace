#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

/* �����, �������� � ���� ���������� � ������������ ���� �������� */
class CCollisionEvent
{
public:
	/* ������ ������, ������������� �� ������ */
	ex::Entity firstEntity;

	/* ������ ������, ������������� � ������ */
	ex::Entity secondEntity;

	/* ������� ����������� */
	CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity);
};

#endif