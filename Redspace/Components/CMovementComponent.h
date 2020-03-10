#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

/* Компонент для перемещения */
class CMovementComponent
{
private:
	/* Максимальная скорость */
	float maxSpeed;

	/* Скорость */
	float speed;

	/* Направление (от -1.0f до 1.0f) */
	sf::Vector2f direction;

public:
	/* Базовый конструктор */
	CMovementComponent(float maxSpeed);

	/* Возвращает вектор скорости */
	const sf::Vector2f& getSpeed(ex::TimeDelta timeDelta);
	
	/* Устанавливает направление для скорости */
	void setDirection(float x, float y);

	/* Добавляет ускорение к скорости */
	void addAcceleration(float acceleration);
};

#endif