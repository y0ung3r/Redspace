#ifndef CENEMYSYSTEM_H
#define CENEMYSYSTEM_H

class CEnemySystem : public ex::System<CEnemySystem>
{
private:
	CVectorHelper& vectorHelper;

	sf::RenderWindow& target;

	ex::Entity::Id mapId;

	int count;

public:
	CEnemySystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id mapId, int count);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif