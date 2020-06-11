#ifndef CMOVEMENTSYSTEM_H
#define CMOVEMENTSYSTEM_H

class CMovementSystem : public ex::System<CMovementSystem>
{
private:
	CVectorHelper& vectorHelper;

	sf::RenderWindow& target;

public:
	explicit CMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif