#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Core/CGame.h"
#include "../Enums/GameStates.h"
#include "../Components/CRenderingComponent.h"

#include "CCursorSystem.h"

CCursorSystem::CCursorSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CCursorSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	std::map<std::string, sf::Cursor*> cursors = CAssetsHelper::getInstance().getCursors();

	if (CGame::isGameState(GameStates::Unpaused))
	{
		this->target.setMouseCursor(*cursors["csr_crosshair"]);
	}
	else if (CGame::isGameState(GameStates::Paused))
	{
		this->target.setMouseCursor(*cursors["csr_ship"]);
	}
}