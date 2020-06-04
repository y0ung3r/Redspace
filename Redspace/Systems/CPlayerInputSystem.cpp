#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>
#include <optional>

namespace ex = entityx;

#include "../Events/CMouseInputEvent.h"
#include "../Components/CInputComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CRotationComponent.h"

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

	for (ex::Entity entity : entities.entities_with_components(inputComponent))
	{
		ex::ComponentHandle<CMovementComponent> playerMovementComponent;
		ex::ComponentHandle<CRotationComponent> playerRotationComponent;

		if (this->mouseButton == sf::Mouse::Right && entity.has_component<CMovementComponent>() && entity.has_component<CRotationComponent>())
		{
			playerMovementComponent = entity.component<CMovementComponent>();
			playerRotationComponent = entity.component<CRotationComponent>();

			sf::Vector2i mousePositionInPixels = sf::Mouse::getPosition(this->target);
			sf::Vector2f mousePositionInCoords = this->target.mapPixelToCoords(mousePositionInPixels);

			playerMovementComponent->moveTo = mousePositionInCoords;
			playerMovementComponent->mustMove = true;

			playerRotationComponent->rotateTo = mousePositionInCoords;
			playerRotationComponent->mustRotate = true;

			this->mouseButton = sf::Mouse::Button(); // Найти более достойный вариант очистки этой переменной!
		}
	}
}

void CPlayerInputSystem::receive(const CMouseInputEvent& mouseInputEvent)
{
	this->mouseButton = mouseInputEvent.instance.button;
}
