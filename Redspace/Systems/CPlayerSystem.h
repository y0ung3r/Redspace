#ifndef CPLAYERSYSTEM_H
#define CPLAYERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Helpers/CVectorHelper.h"
#include "../Components/CRenderComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CPlayerComponent.h"

namespace ex = entityx;

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
	explicit CPlayerSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId)
		: vectorHelper(vectorHelper), target(target), playerId(playerId)
	{ }

	/* ќбновл€ет систему перемещени€ игрока */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif