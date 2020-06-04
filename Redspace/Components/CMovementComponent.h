#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

class CMovementComponent;

/* Компонент для перемещения */
class CMovementComponent
{
public:
	/* Должен ли объект перемещаться? */
	bool mustMove = false;

	/* Координаты объекта, по отношению к которому производится перемещение */
	sf::Vector2f moveTo;

	/* Скорость */
	float speed = 250.0f;
};

#endif