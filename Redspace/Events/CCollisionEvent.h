#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

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
	CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity);

	const ex::Entity& getFirstEntity() const;

	const ex::Entity& getSecondEntity() const;
};

#endif