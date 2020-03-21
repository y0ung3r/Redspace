#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Helpers/CAssetsHelper.h"
#include "../Core/CGame.h"
#include "../Enums/GameStates.h"
#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* �������, ����������� ������� ��������� ������� */
class CCursorSystem : public ex::System<CCursorSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CCursorSystem(sf::RenderWindow& target)
		: target(target)
	{ }

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif

