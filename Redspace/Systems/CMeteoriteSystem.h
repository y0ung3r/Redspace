#ifndef CMETEORITESYSTEM_H
#define CMETEORITESYSTEM_H

#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Helpers/CAssetsHelper.h"
#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CCollisionComponent.h"
#include "../Components/CMeteoriteComponent.h"
#include "../Events/CCollisionEvent.h"

namespace ex = entityx;

/* Система, управляющая поведением метеоритов */
class CMeteoriteSystem : public ex::System<CMeteoriteSystem>, public ex::Receiver<CMeteoriteSystem>
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Идентификатор карты */
	ex::Entity::Id mapId;

	ex::Entity firstCollidedMeteorite;

	ex::Entity secondCollidedMeteorite;

	/* Количество метеоритов */
	int count;

public:
	/* Базовый конструктор */
	CMeteoriteSystem(sf::RenderWindow& target, ex::Entity::Id mapId, int count)
		: target(target), mapId(mapId), count(count)
	{ } 

	/* Настраивает менеджер событий для данной системы */
	void configure(ex::EventManager& events) override;

	/* Обновляет систему управления метеоритами */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	/* Выполняет получение столкнувшихся метеоритов */
	void receive(const CCollisionEvent& collisionEvent);
};

#endif