#ifndef CMETEORITESYSTEM
#define CMETEORITESYSTEM

#include <random>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"

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