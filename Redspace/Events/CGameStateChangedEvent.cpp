#include "../Enums/GameStates.h"

#include "CGameStateChangedEvent.h"

CGameStateChangedEvent::CGameStateChangedEvent(GameStates gameState)
	: gameState(gameState)
{ }

GameStates CGameStateChangedEvent::getGameState() const
{
	return this->gameState;
}
