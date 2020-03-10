#ifndef CGAME_H
#define CGAME_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CCameraComponent.h"
#include "../Systems/CRenderSystem.h"
#include "../Systems/CCursorSystem.h"
#include "../Systems/CCameraSystem.h"
#include "../Systems/CPlayerSystem.h"
#include "../Systems/CMeteoriteSystem.h"

namespace ex = entityx;

/* �������� ����� ���� */
class CGame : public ex::EntityX
{
private:
	sf::RenderWindow& target;

	/* ������� ����� � ���������� �� ������������� */
	ex::Entity::Id createMap();

	/* ������� ������ � ���������� ��� ������������� */
	ex::Entity::Id createCursor();

	/* ������� ������ ������ � ���������� ��� ������������� */
	ex::Entity::Id createCamera();

	/* ������� ������ � ���������� ��� ������������� */
	ex::Entity::Id createPlayer();

public:
	/* ������� ����������� */
	explicit CGame(sf::RenderWindow& target);

	/* ��������� ���� */
	void update(ex::TimeDelta timeDelta);
};

#endif