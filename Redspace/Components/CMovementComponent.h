#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

class CMovementComponent;

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
	CMovementComponent(float initialSpeed = 0.0f, float maxSpeed = 50.0f);

	/* ���������� ������ �������� */
	const sf::Vector2f& getSpeed(ex::TimeDelta timeDelta);

	/* ���������� ����������� �������� (�� -1.0f �� 1.0f) */
	const sf::Vector2f& getDirection();

	/* ������������� ����������� ��� �������� */
	void setDirection(float x, float y);

	/* ��������� ��������� � �������� */
	void addAcceleration(float acceleration);
};

#endif