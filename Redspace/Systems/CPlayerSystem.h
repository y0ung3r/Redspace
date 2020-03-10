#ifndef CPLAYERSYSTEM_H
#define CPLAYERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Helpers/CVectorHelper.h"

namespace ex = entityx;

/* �������, ����������� ������� ����������� ������ */
class CPlayerSystem : public ex::System<CPlayerSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;
	
	/* ������������� ������ */
	ex::Entity::Id playerId;

public:
	/* ������� ����������� */
	explicit CPlayerSystem(sf::RenderWindow& target, ex::Entity::Id& playerId)
		: target(target), playerId(playerId)
	{ }

	/* ��������� ������� ����������� ������ */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif