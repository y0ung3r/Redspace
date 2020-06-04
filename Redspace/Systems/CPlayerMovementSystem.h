#ifndef CPLAYERMOVEMENTSYSTEM_H
#define CPLAYERMOVEMENTSYSTEM_H

class CPlayerMovementSystem;
class CVectorHelper;

/* —истема, управл€юща€ логикой перемещени€ игрока */
class CPlayerMovementSystem : public ex::System<CPlayerMovementSystem>
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

	/* ќбновл€ет систему перемещени€ игрока */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif