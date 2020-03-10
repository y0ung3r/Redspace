#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

#include <SFML/Graphics.hpp>
#include "entityx/entityx.h"

#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* �������, ����������� ������� ��������� ������� */
class CCursorSystem : public ex::System<CCursorSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������������� ������� */
	ex::Entity::Id cursorId;

public:
	/* ������� ����������� */
	explicit CCursorSystem(sf::RenderWindow& target, ex::Entity::Id& cursorId)
		: target(target), cursorId(cursorId)
	{ }

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif

