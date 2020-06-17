#ifndef CMOVEMENTSYSTEM_H
#define CMOVEMENTSYSTEM_H

#include "../Core/CGame.h"

class CMovementSystem : public ex::System<CMovementSystem>
{
private:
	CGame& game;

	CVectorHelper& vectorHelper;

	sf::RenderWindow& target;

public:
	explicit CMovementSystem(CGame& game, CVectorHelper& vectorHelper, sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif