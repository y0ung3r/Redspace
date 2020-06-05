#ifndef CPLAYERMOVEMENTSYSTEM_H
#define CPLAYERMOVEMENTSYSTEM_H

class CCollisionEvent;

/* —истема, управл€юща€ логикой перемещени€ игрока */
class CPlayerMovementSystem : public ex::System<CPlayerMovementSystem>, public ex::Receiver<CPlayerMovementSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* —сылка на окно */
	sf::RenderWindow& target;
	
	/* »дентификатор игрока */
	ex::Entity::Id playerId;

public:
	/* Ѕазовый конструктор */
	explicit CPlayerMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId);

	void configure(ex::EventManager& events) override;

	/* ќбновл€ет систему перемещени€ игрока */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CCollisionEvent& collisionEvent);
};

#endif