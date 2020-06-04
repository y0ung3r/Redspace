#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CVectorHelper.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CRotationComponent.h"
#include "../Components/CPlayerComponent.h"

#include "CPlayerRotationSystem.h"

CPlayerRotationSystem::CPlayerRotationSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId)
	: vectorHelper(vectorHelper), target(target), playerId(playerId)
{ }

void CPlayerRotationSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity player = entities.get(this->playerId);

	ex::ComponentHandle<CRenderingComponent> playerRenderingComponent = player.component<CRenderingComponent>();
	ex::ComponentHandle<CRotationComponent> playerRotationComponent = player.component<CRotationComponent>();
	ex::ComponentHandle<CPlayerComponent> playerComponent = player.component<CPlayerComponent>();

	sf::Vector2f playerPosition = playerRenderingComponent->getPosition();

	if (playerRotationComponent->mustRotate)
	{
		float playerAngleRotate = playerRenderingComponent->getRotation();
		float destinationAngleRotate = vectorHelper.getAngleInDegrees(playerRotationComponent->rotateTo, playerPosition);

		float difference = destinationAngleRotate - playerAngleRotate;
		float absoluteDifference = std::fabsf(difference);
		float direction = difference / absoluteDifference;

		float absoluteSpeed = static_cast<float>(timeDelta) * playerRotationComponent->rotationSpeed;
		float destinationSpeed = direction * absoluteSpeed;

		if (absoluteDifference > absoluteSpeed)
		{
			// TO DO: ¬ыбирать оптимальное направление поворота в зависимости от углов
			playerRenderingComponent->rotate(destinationSpeed);
		}
		else
		{
			playerRotationComponent->mustRotate = false;
		}
	}
}
