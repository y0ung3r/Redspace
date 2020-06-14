#ifndef CMOVEMENTSYSTEM_H
#define CMOVEMENTSYSTEM_H

class CMovementSystem : public ex::System<CMovementSystem>
{
private:
	CVectorHelper& vectorHelper;

	sf::RenderWindow& target;

	ex::Entity::Id mapId;

public:
	explicit CMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id mapId);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif