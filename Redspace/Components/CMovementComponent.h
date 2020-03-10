#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

/* Компонент для перемещения */
class CMovementComponent
{
private:
	/* Скорость */
	float speed;

	/* Максимальная скорость */
	float maxSpeed;

	/* Направление (от -1.0f до 1.0f) */
	sf::Vector2f direction;

public:
	/* Базовый конструктор */
	CMovementComponent(float startSpeed = 0.0f, float maxSpeed = 50.0f)
		: speed(startSpeed), maxSpeed(maxSpeed), direction(sf::Vector2f(0.0f, 0.0f))
	{ }

	/* Возвращает вектор скорости */
	const sf::Vector2f& getSpeed(ex::TimeDelta timeDelta);

	/* Устанавливает направление для скорости */
	void setDirection(float x, float y);

	/* Добавляет ускорение к скорости */
	void addAcceleration(float acceleration);
};

#endif