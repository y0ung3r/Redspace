#ifndef CGAME_H
#define CGAME_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Enums/GameStates.h"
#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Components/CRenderComponent.h"
#include "../Components/CCameraComponent.h"
#include "../Components/CPlayerComponent.h"
#include "../Systems/CRenderSystem.h"
#include "../Systems/CCursorSystem.h"
#include "../Systems/CCameraSystem.h"
#include "../Systems/CPlayerSystem.h"
#include "../Systems/CMeteoriteSystem.h"
#include "../Systems/CCollisionSystem.h"

namespace ex = entityx;

/* �������� ����� ���� */
class CGame : public ex::EntityX
{
private:
	/* ������� ������� ��������� */
	static GameStates gameState;

	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������� ����� � ���������� �� ������������� */
	ex::Entity::Id createMap();

	/* ������� ������ ������ � ���������� ��� ������������� */
	ex::Entity::Id createCamera();

	/* ������� ������ � ���������� ��� ������������� */
	ex::Entity::Id createPlayer();

public:
	/* ������� ����������� */
	explicit CGame(sf::RenderWindow& target);

	/* ��������� ���� */
	void update(ex::TimeDelta timeDelta);

	/* ���������� ������, ���� ������� ������� ��������� ��������� � ���������� � �������� ��������� */
	static bool isGameState(GameStates gameState);
};

#endif