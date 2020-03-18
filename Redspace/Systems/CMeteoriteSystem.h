#ifndef CMETEORITESYSTEM_H
#define CMETEORITESYSTEM_H

#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Helpers/CAssetsHelper.h"
#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CMeteoriteComponent.h"

namespace ex = entityx;

/* �������, ����������� ���������� ���������� */
class CMeteoriteSystem : public ex::System<CMeteoriteSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������������� ����� */
	ex::Entity::Id mapId;

	/* ���������� ���������� */
	int count;

public:
	/* ������� ����������� */
	CMeteoriteSystem(sf::RenderWindow& target, ex::Entity::Id mapId, int count)
		: target(target), mapId(mapId), count(count)
	{ } 

	/* ��������� ������� ���������� ����������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif