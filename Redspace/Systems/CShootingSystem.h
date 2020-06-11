#ifndef CSHOOTINGSYSTEM_H
#define CSHOOTINGSYSTEM_H

class CSingleMouseInputEvent;

class CShootingSystem : public ex::System<CShootingSystem>
{
private:
	IObjectFactory& bulletFactory;

	sf::RenderWindow& target;

public:
	explicit CShootingSystem(IObjectFactory& bulletFactory, sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif