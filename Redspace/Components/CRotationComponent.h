#ifndef CROTATIONCOMPONENT_H
#define CROTATIONCOMPONENT_H

/* ��������� �������� ������ ����� ��� */
class CRotationComponent
{
public:
	/* ������ �� ������ ���������? */
	bool mustRotate = false;

	/* ���������� �������, �� ��������� � �������� ������������ �������� */
	sf::Vector2f rotateTo;

	/* �������� �������� */
	float rotationSpeed = 350.0f;
};

#endif