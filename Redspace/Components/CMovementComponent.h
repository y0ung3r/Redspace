#ifndef CMOVEMENTCOMPONENT_H
#define CMOVEMENTCOMPONENT_H

class CMovementComponent;

/* ��������� ��� ����������� */
class CMovementComponent
{
public:
	/* ������ �� ������ ������������? */
	bool mustMove = false;

	/* ���������� �������, �� ��������� � �������� ������������ ����������� */
	sf::Vector2f moveTo;

	/* �������� */
	float speed = 250.0f;
};

#endif