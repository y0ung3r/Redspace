#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

class CMovementComponent;

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
	CMovementComponent(float initialSpeed = 0.0f, float maxSpeed = 50.0f);

	/* Возвращает вектор скорости */
	const sf::Vector2f& getSpeed(ex::TimeDelta timeDelta);

	/* Возвращает направление скорости (от -1.0f до 1.0f) */
	const sf::Vector2f& getDirection();

	/* Устанавливает направление для скорости */
	void setDirection(float x, float y);

	/* Добавляет ускорение к скорости */
	void addAcceleration(float acceleration);
};

#endif