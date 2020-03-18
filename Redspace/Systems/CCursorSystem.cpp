#include "CCursorSystem.h"

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