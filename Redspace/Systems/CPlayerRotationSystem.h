#ifndef CPLAYERROTATIONSYSTEM_H
#define CPLAYERROTATIONSYSTEM_H

class CPlayerRotationSystem : public ex::System<CPlayerRotationSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Идентификатор игрока */
	ex::Entity::Id playerId;

public:
	/* Базовый конструктор */
	explicit CPlayerRotationSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId);

	/* Обновляет систему перемещения игрока */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif