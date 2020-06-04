#ifndef CROTATIONCOMPONENT_H
#define CROTATIONCOMPONENT_H

/* Компонент вращения вокруг своей оси */
class CRotationComponent
{
public:
	/* Должен ли объект вращаться? */
	bool mustRotate = false;

	/* Координаты объекта, по отношению к которому производится вращение */
	sf::Vector2f rotateTo;

	/* Скорость вращения */
	float rotationSpeed = 350.0f;
};

#endif