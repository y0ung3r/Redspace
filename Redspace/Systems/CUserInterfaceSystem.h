#ifndef CUSERINTERFACESYSTEM_H
#define CUSERINTERFACESYSTEM_H

#include "../Core/CGame.h"

class CUserInterfaceSystem : public ex::System<CUserInterfaceSystem>
{
private:
	CGame& game;

	sf::RenderWindow& target;

public:
	explicit CUserInterfaceSystem(CGame& game, sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif