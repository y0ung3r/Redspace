#ifndef CBULLETSYSTEM_H
#define CBULLETSYSTEM_H

class CCollisionEvent;
class CLostVisibilityEvent;

class CBulletSystem : public ex::System<CBulletSystem>, public ex::Receiver<CBulletSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

	std::vector<ex::Entity> listOfDestruction;

public:
	/* Ѕазовый конструктор */
	explicit CBulletSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CCollisionEvent& collisionEvent);

	void receive(const CLostVisibilityEvent& lostVisibilityEvent);

	void receive(const ex::EntityDestroyedEvent& entityDestroyedEvent);
};

#endif