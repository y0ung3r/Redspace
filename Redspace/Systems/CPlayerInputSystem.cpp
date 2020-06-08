#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>
#include <optional>

namespace ex = entityx;

#include "../Events/CMouseInputEvent.h"
#include "../Components/CInputComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CRotationComponent.h"
#include "../Components/CCircleBorderComponent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CEnemyComponent.h"

#include "CPlayerInputSystem.h"

CPlayerInputSystem::CPlayerInputSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CPlayerInputSystem::configure(ex::EventManager& events)
{
	events.subscribe<CMouseInputEvent>(*this);
}

void CPlayerInputSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CInputComponent> inputComponent;
	ex::ComponentHandle<CMovementComponent> playerMovementComponent;
	ex::ComponentHandle<CRotationComponent> playerRotationComponent;

	for (ex::Entity entity : entities.entities_with_components(inputComponent, playerMovementComponent, playerRotationComponent))
	{
		ex::ComponentHandle<CRenderingComponent> nearbyObjectRenderingComponent;
		ex::ComponentHandle<CCircleBorderComponent> nearbyObjectCircleBorderComponent;

		sf::Vector2i mousePositionInPixels = sf::Mouse::getPosition(this->target);
		sf::Vector2f mousePositionInCoords = this->target.mapPixelToCoords(mousePositionInPixels);

		if (this->mouseButton == sf::Mouse::Left || this->mouseButton == sf::Mouse::Right)
		{
			for (ex::Entity nearbyEntity : entities.entities_with_components(nearbyObjectRenderingComponent, nearbyObjectCircleBorderComponent))
			{
				nearbyObjectCircleBorderComponent->isVisible = false;

				sf::FloatRect nearbyObjectGlobalBounds = nearbyObjectRenderingComponent->getGlobalBounds();

				if (nearbyObjectGlobalBounds.contains(mousePositionInCoords))
				{
					nearbyObjectCircleBorderComponent->isVisible = true;
				}
			}
		}

		if (this->mouseButton == sf::Mouse::Right)
		{
			playerMovementComponent->moveTo = mousePositionInCoords;
			playerMovementComponent->mustMove = true;

			playerRotationComponent->rotateTo = mousePositionInCoords;
			playerRotationComponent->mustRotate = true;
		}
	}

	this->mouseButton = sf::Mouse::Button::ButtonCount; // Найти более достойный вариант очистки этой переменной!
}

void CPlayerInputSystem::receive(const CMouseInputEvent& mouseInputEvent)
{
	this->mouseButton = mouseInputEvent.instance.button;
}
