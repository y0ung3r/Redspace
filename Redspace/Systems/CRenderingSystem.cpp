#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Components/CRenderingComponent.h"

#include "CRenderingSystem.h"

CRenderingSystem::CRenderingSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CRenderingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent))
	{
		CRenderingComponent instance = *entityRenderingComponent.get();
		this->target.draw(instance);

		{
			sf::RectangleShape rectangleShape;

			sf::FloatRect entityGlobalBounds = entityRenderingComponent->getGlobalBounds();

			sf::Vector2f rectangleShapeSize(entityGlobalBounds.width, entityGlobalBounds.height);
			rectangleShape.setSize(rectangleShapeSize);

			rectangleShape.setPosition(entityGlobalBounds.left, entityGlobalBounds.top);

			rectangleShape.setFillColor(sf::Color::Transparent);
			rectangleShape.setOutlineThickness(1.0f);
			rectangleShape.setOutlineColor(sf::Color::White);

			this->target.draw(rectangleShape);
		}
	}
}