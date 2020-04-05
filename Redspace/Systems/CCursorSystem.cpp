#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Core/CGame.h"
#include "../Enums/GameStates.h"
#include "../Components/CRenderComponent.h"

#include "CCursorSystem.h"

CCursorSystem::CCursorSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CCursorSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	std::vector<sf::Cursor*> cursors = CAssetsHelper::getInstance().getCursors();

	if (CGame::isGameState(GameStates::Unpaused))
	{
		this->target.setMouseCursor(*cursors[0]);
	}
	else if (CGame::isGameState(GameStates::Paused))
	{
		this->target.setMouseCursor(*cursors[1]);
	}
}