#ifndef CCAMERASYSTEM_H
#define CCAMERASYSTEM_H

#include <SFML/Graphics.hpp>
#include "entityx/entityx.h"

#include "../Components/CCameraComponent.h"
#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* �������, ����������� ������� ��������� ������ */
class CCameraSystem : public ex::System<CCameraSystem>
{
private:
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
	explicit CCameraSystem(sf::RenderWindow& target, ex::Entity::Id cameraId, ex::Entity::Id mapId, ex::Entity::Id objectId)
		: target(target), cameraId(cameraId), mapId(mapId), objectId(objectId)
	{ }

	/* ��������� ������� ���������� ������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif