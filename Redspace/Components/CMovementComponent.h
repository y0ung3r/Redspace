#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

/* ��������� ��� ����������� */
class CMovementComponent
{
private:
	/* �������� */
	float speed;

	/* ������������ �������� */
	float maxSpeed;

	/* ����������� (�� -1.0f �� 1.0f) */
	sf::Vector2f direction;

public:
	/* ������� ����������� */
	CMovementComponent(float startSpeed = 0.0f, float maxSpeed = 50.0f)
		: speed(startSpeed), maxSpeed(maxSpeed), direction(sf::Vector2f(0.0f, 0.0f))
	{ }

	/* ���������� ������ �������� */
	const sf::Vector2f& getSpeed(ex::TimeDelta timeDelta);

	/* ������������� ����������� ��� �������� */
	void setDirection(float x, float y);

	/* ��������� ��������� � �������� */
	void addAcceleration(float acceleration);
};

#endif