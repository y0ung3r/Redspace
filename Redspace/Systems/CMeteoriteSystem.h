#ifndef CMETEORITESYSTEM_H
#define CMETEORITESYSTEM_H

class CMeteoriteSystem;
class CCollisionEvent;

/* Система, управляющая поведением метеоритов */
class CMeteoriteSystem : public ex::System<CMeteoriteSystem>, public ex::Receiver<CMeteoriteSystem>
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Идентификатор карты */
	ex::Entity::Id mapId;

	/* Первый столкнувшийся метеорит */
	ex::Entity firstCollidedMeteorite;

	/* Второй столкнувшийся метеорит */
	ex::Entity secondCollidedMeteorite;

	/* Количество метеоритов */
	int count;

public:
	/* Базовый конструктор */
	CMeteoriteSystem(sf::RenderWindow& target, ex::Entity::Id mapId, int count);

	/* Настраивает менеджер событий для данной системы */
	void configure(ex::EventManager& events) override;

	/* Обновляет систему управления метеоритами */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	/* Выполняет получение столкнувшихся метеоритов */
	void receive(const CCollisionEvent& collisionEvent);
};

#endif