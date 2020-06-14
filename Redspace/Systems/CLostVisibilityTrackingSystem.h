#ifndef CLOSTVISIBILITYTRACKINGSYSTEM_H
#define CLOSTVISIBILITYTRACKINGSYSTEM_H

#include "../Core/CGame.h"

class CLostVisibilityTrackingSystem : public ex::System<CLostVisibilityTrackingSystem>
{
private:
	CGame& game;

	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CLostVisibilityTrackingSystem(CGame& game, sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif