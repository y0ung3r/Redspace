#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

/* Класс, хранящий в себе информацию о столкновении двух объектов */
class CCollisionEvent
{
public:
	/* Первый объект, столкнувшийся со вторым */
	ex::Entity firstEntity;

	/* Второй объект, столкнувшийся с первым */
	ex::Entity secondEntity;

	/* Базовый конструктор */
	CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity);
};

#endif