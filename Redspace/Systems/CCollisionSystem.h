#ifndef CCOLLISIONSYSTEM_H
#define CCOLLISIONSYSTEM_H

class CCollisionSystem;

/* —истема, управл€юща€ логикой столкновени€ объектов */
class CCollisionSystem : public ex::System<CCollisionSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CCollisionSystem(sf::RenderWindow& target);

	/* ќбновл€ет систему столкновений объектов */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif