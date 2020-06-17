#ifndef CSHOOTINGSYSTEM_H
#define CSHOOTINGSYSTEM_H

class CSingleMouseInputEvent;

#include "../Core/CGame.h"

class CShootingSystem : public ex::System<CShootingSystem>
{
private:
	CGame& game;

	CVectorHelper& vectorHelper;

	IObjectFactory& bulletFactory;

	sf::RenderWindow& target;

public:
	explicit CShootingSystem(CGame& game, CVectorHelper& vectorHelper, IObjectFactory& bulletFactory, sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif