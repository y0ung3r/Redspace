#ifndef CGAMESTATECHANGEDEVENT_H
#define CGAMESTATECHANGEDEVENT_H

class CGameStateChangedEvent
{
private:
	GameStates gameState;

public:
	CGameStateChangedEvent(GameStates gameState);

	GameStates getGameState() const;
};

#endif