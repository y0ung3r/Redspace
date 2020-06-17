#ifndef CCOLLISIONTRACKINGSYSTEM_H
#define CCOLLISIONTRACKINGSYSTEM_H

class CCollisionTrackingSystem;

/* —истема, управл€юща€ логикой столкновени€ объектов */
class CCollisionTrackingSystem : public ex::System<CCollisionTrackingSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CCollisionTrackingSystem(sf::RenderWindow& target);

	/* ќбновл€ет систему столкновений объектов */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif