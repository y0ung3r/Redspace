#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Components/CRenderComponent.h"

#include "CRenderSystem.h"

CRenderSystem::CRenderSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CRenderSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderComponent> renderComponent;

	for (ex::Entity entity : entities.entities_with_components(renderComponent))
	{
		this->target.draw(*renderComponent.get());

		/* Код отрисовки границ у всех объектах */
		{
			sf::RectangleShape rectangleShape;

			sf::FloatRect renderGlobalBounds = renderComponent->getGlobalBounds();

			sf::Vector2f rectangleShapeSize;
			rectangleShapeSize.x = renderGlobalBounds.width;
			rectangleShapeSize.y = renderGlobalBounds.height;
			rectangleShape.setSize(rectangleShapeSize);
			rectangleShape.setPosition(renderGlobalBounds.left, renderGlobalBounds.top);

			rectangleShape.setFillColor(sf::Color::Transparent);
			rectangleShape.setOutlineThickness(1.0f);

			sf::Color renderColor = renderComponent->getColor();
			rectangleShape.setOutlineColor(renderColor);

			this->target.draw(rectangleShape);
		}
	}
}