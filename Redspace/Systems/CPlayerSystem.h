#ifndef CPLAYERSYSTEM_H
#define CPLAYERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Helpers/CVectorHelper.h"
#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CPlayerComponent.h"

namespace ex = entityx;

/* �������, ����������� ������� ����������� ������ */
class CPlayerSystem : public ex::System<CPlayerSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* ������ �� ���� */
	sf::RenderWindow& target;
	
	/* ������������� ������ */
	ex::Entity::Id playerId;

public:
	/* ������� ����������� */
	explicit CPlayerSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId)
		: vectorHelper(vectorHelper), target(target), playerId(playerId)
	{ }

	/* ��������� ������� ����������� ������ */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif