#ifndef CENEMYSYSTEM_H
#define CENEMYSYSTEM_H

class CEnemySystem : public ex::System<CEnemySystem>, public ex::Receiver<CEnemySystem>
{
private:
	IObjectFactory& enemyFactory;

	sf::RenderWindow& target;

	ex::Entity::Id mapId;

	int maxCount;

public:
	explicit CEnemySystem(IObjectFactory& enemyFactory, sf::RenderWindow& target, ex::Entity::Id mapId, int count);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const ex::EntityDestroyedEvent& entityDestroyedEvent);
};

#endif