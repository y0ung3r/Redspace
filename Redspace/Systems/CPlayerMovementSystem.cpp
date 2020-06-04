#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CVectorHelper.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CPlayerComponent.h"

#include "CPlayerMovementSystem.h"

CPlayerMovementSystem::CPlayerMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId)
	: vectorHelper(vectorHelper), target(target), playerId(playerId)
{ }

void CPlayerMovementSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity player = entities.get(this->playerId);

	ex::ComponentHandle<CRenderingComponent> playerRenderingComponent = player.component<CRenderingComponent>();
	ex::ComponentHandle<CMovementComponent> playerMovementComponent = player.component<CMovementComponent>();
	ex::ComponentHandle<CPlayerComponent> playerComponent = player.component<CPlayerComponent>();

	sf::Vector2f playerPosition = playerRenderingComponent->getPosition();

	if (playerMovementComponent->mustMove)
	{
		sf::Vector2f difference = playerMovementComponent->moveTo - playerPosition;
		sf::Vector2f direction = vectorHelper.getOrt(difference);

		float distance = vectorHelper.getLength(difference);

		if (distance >= 1.0f)
		{
			playerRenderingComponent->move(playerMovementComponent->speed * static_cast<float>(timeDelta) * direction);
		}
		else
		{
			playerMovementComponent->mustMove = false;
		}
	}
}