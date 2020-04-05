#ifndef CCOLLISIONEVENT_H
#define CCOLLISIONEVENT_H

/* Класс, хранящий в себе информацию о столкновении двух объектов */
class CCollisionEvent
{
private:
	/* Первый объект, столкнувшийся со вторым */
	ex::Entity firstEntity;

	/* Второй объект, столкнувшийся с первым */
	ex::Entity secondEntity;

public:
	/* Базовый конструктор */
	CCollisionEvent(const ex::Entity& firstEntity, const ex::Entity& secondEntity);

	/* Возвращает первый объект */
	const ex::Entity& getFirstEntity() const;

	/* Возвращает второй объект */
	const ex::Entity& getSecondEntity() const;
};

#endif