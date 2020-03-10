#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

/* ��������� ��� ����������� */
class CMovementComponent
{
private:
	/* ������������ �������� */
	float maxSpeed;

	/* �������� */
	float speed;

	/* ����������� (�� -1.0f �� 1.0f) */
	sf::Vector2f direction;

public:
	/* ������� ����������� */
	CMovementComponent(float maxSpeed);

	/* ���������� ������ �������� */
	const sf::Vector2f& getSpeed(ex::TimeDelta timeDelta);
	
	/* ������������� ����������� ��� �������� */
	void setDirection(float x, float y);

	/* ��������� ��������� � �������� */
	void addAcceleration(float acceleration);
};

#endif