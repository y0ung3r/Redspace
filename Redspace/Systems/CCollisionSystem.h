#ifndef CCOLLISIONSYSTEM_H
#define CCOLLISIONSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CCollisionComponent.h"
#include "../Events/CCollisionEvent.h"

namespace ex = entityx;

/* —истема, управл€юща€ логикой столкновени€ объектов */
class CCollisionSystem : public ex::System<CCollisionSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CCollisionSystem(sf::RenderWindow& target)
		: target(target)
	{ }

	/* ќбновл€ет систему столкновений объектов */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif