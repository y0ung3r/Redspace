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
	ex::ComponentHandle<CRenderingComponent> renderingComponent;

	for (ex::Entity entity : entities.entities_with_components(renderingComponent))
	{
		this->target.draw(*renderingComponent.get());

		/* Код отрисовки границ у всех объектов */
		/*sf::RectangleShape rectangleShape;

		sf::FloatRect renderingGlobalBounds = renderingComponent->getGlobalBounds();

		sf::Vector2f rectangleShapeSize;
		rectangleShapeSize.x = renderingGlobalBounds.width;
		rectangleShapeSize.y = renderingGlobalBounds.height;
		rectangleShape.setSize(rectangleShapeSize);
		rectangleShape.setPosition(renderingGlobalBounds.left, renderingGlobalBounds.top);

		rectangleShape.setFillColor(sf::Color::Transparent);
		rectangleShape.setOutlineThickness(1.0f);

		this->target.draw(rectangleShape);*/
	}
}