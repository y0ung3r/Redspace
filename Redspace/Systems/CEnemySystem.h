#ifndef CENEMYSYSTEM_H
#define CENEMYSYSTEM_H

#include "../Core/CGame.h"

class CEnemySystem : public ex::System<CEnemySystem>, public ex::Receiver<CEnemySystem>
{
private:
	CGame& game;

	IObjectFactory& enemyFactory;

	sf::RenderWindow& target;

	int maxCount;

public:
	explicit CEnemySystem(CGame& game, IObjectFactory& enemyFactory, sf::RenderWindow& target, int count);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const ex::EntityDestroyedEvent& entityDestroyedEvent);
};

#endif