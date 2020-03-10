#ifndef CPLAYERSYSTEM_H
#define CPLAYERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Helpers/CVectorHelper.h"

namespace ex = entityx;

/* —истема, управл€юща€ логикой перемещени€ игрока */
class CPlayerSystem : public ex::System<CPlayerSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;
	
	/* »дентификатор игрока */
	ex::Entity::Id playerId;

public:
	/* Ѕазовый конструктор */
	explicit CPlayerSystem(sf::RenderWindow& target, ex::Entity::Id& playerId)
		: target(target), playerId(playerId)
	{ }

	/* ќбновл€ет систему перемещени€ игрока */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif