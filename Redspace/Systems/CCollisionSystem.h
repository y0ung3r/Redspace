#ifndef CCOLLISIONSYSTEM_H
#define CCOLLISIONSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CCollisionComponent.h"
#include "../Events/CCollisionEvent.h"

namespace ex = entityx;

/* �������, ����������� ������� ������������ �������� */
class CCollisionSystem : public ex::System<CCollisionSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CCollisionSystem(sf::RenderWindow& target)
		: target(target)
	{ }

	/* ��������� ������� ������������ �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif