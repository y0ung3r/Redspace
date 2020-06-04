#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Components/CRenderingComponent.h"
#include "../Components/CCircleBorderComponent.h"
#include "CCircleBorderRenderingSystem.h"

CCircleBorderRenderingSystem::CCircleBorderRenderingSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CCircleBorderRenderingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> nearbyObjectRenderingComponent;
	ex::ComponentHandle<CCircleBorderComponent> nearbyObjectCircleBorderComponent;

	for (ex::Entity entity : entities.entities_with_components(nearbyObjectRenderingComponent, nearbyObjectCircleBorderComponent))
	{
		if (nearbyObjectCircleBorderComponent->isVisible)
		{
			sf::IntRect nearbyObjectSize = nearbyObjectRenderingComponent->getTextureRect();
			float radius = nearbyObjectSize.height / 2 + 35.0f;
			nearbyObjectCircleBorderComponent->circleShape.setRadius(radius);

			sf::Vector2f nearbyObjectCircleShapeOrigin;
			nearbyObjectCircleShapeOrigin.x = radius;
			nearbyObjectCircleShapeOrigin.y = radius;
			nearbyObjectCircleBorderComponent->circleShape.setOrigin(nearbyObjectCircleShapeOrigin);

			nearbyObjectCircleBorderComponent->circleShape.setOutlineColor(sf::Color::Yellow);
			nearbyObjectCircleBorderComponent->circleShape.setOutlineThickness(1.5f);
			nearbyObjectCircleBorderComponent->circleShape.setFillColor(sf::Color::Transparent);

			sf::Vector2f nearbyObjectPosition = nearbyObjectRenderingComponent->getPosition();
			nearbyObjectCircleBorderComponent->circleShape.setPosition(nearbyObjectPosition);

			this->target.draw(nearbyObjectCircleBorderComponent->circleShape);
		}
	}
}
