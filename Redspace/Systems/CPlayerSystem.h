#ifndef CPLAYERSYSTEM_H
#define CPLAYERSYSTEM_H

class CPlayerSystem;
class CVectorHelper;

/* —истема, управл€юща€ логикой перемещени€ игрока */
class CPlayerSystem : public ex::System<CPlayerSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* —сылка на окно */
	sf::RenderWindow& target;
	
	/* »дентификатор игрока */
	ex::Entity::Id playerId;

public:
	/* Ѕазовый конструктор */
	explicit CPlayerSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId);

	/* ќбновл€ет систему перемещени€ игрока */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif