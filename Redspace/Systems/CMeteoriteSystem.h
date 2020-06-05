#ifndef CMETEORITESYSTEM_H
#define CMETEORITESYSTEM_H

class CMeteoriteSystem;
class CCollisionEvent;

class CMeteoriteSystem : public ex::System<CMeteoriteSystem>, public ex::Receiver<CMeteoriteSystem>
{
private:
	sf::RenderWindow& target;

	ex::Entity::Id mapId;

	int count;

public:
	CMeteoriteSystem(sf::RenderWindow& target, ex::Entity::Id mapId, int count);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CCollisionEvent& collisionEvent);
};

#endif