#ifndef CMETEORITESYSTEM_H
#define CMETEORITESYSTEM_H

#include "../Core/CGame.h"

class CMeteoriteSystem : public ex::System<CMeteoriteSystem>, public ex::Receiver<CMeteoriteSystem>
{
private:
	CGame& game;

	sf::RenderWindow& target;

	IObjectFactory& meteoriteFactory;

	int maxCount;

public:
	CMeteoriteSystem(IObjectFactory& meteoriteFactory, CGame& game, sf::RenderWindow& target, int maxCount);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const ex::EntityDestroyedEvent& entityDestroyedEvent);
};
#endif