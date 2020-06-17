#ifndef CCAMERASYSTEM_H
#define CCAMERASYSTEM_H

#include "../Core/CGame.h"

/* �������, ����������� ������� ��������� ������ */
class CCameraSystem : public ex::System<CCameraSystem>
{
private:
	CGame& game;

	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������������� ������ */
	ex::Entity::Id cameraId;

	/* ������������� ����� */
	ex::Entity::Id mapId;

	/* ������������� �������, � �������� ��������� ������ */
	ex::Entity::Id objectId;

public:
	/* ������� ����������� */
	explicit CCameraSystem(CGame& game, sf::RenderWindow& target);

	/* ��������� ������� ���������� ������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif