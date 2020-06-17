#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"

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

		/*ex::ComponentHandle<CTagComponent> entityTagComponent = entity.component<CTagComponent>();
		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag != ObjectTypes::Map && entityTag != ObjectTypes::Camera)
		{
			sf::RectangleShape rectangleShape;

			sf::Vector2u entityTextureSizeInPixels = entityRenderingComponent->getTexture()->getSize();
			sf::Vector2f entityTextureSizeInCoords = static_cast<sf::Vector2f>(entityTextureSizeInPixels);
			rectangleShape.setSize(entityTextureSizeInCoords);

			sf::Vector2f entityOrigin = entityRenderingComponent->getOrigin();
			rectangleShape.setOrigin(entityOrigin);

			sf::Vector2f entityPosition = entityRenderingComponent->getPosition();
			rectangleShape.setPosition(entityPosition);

			float entityAngleRotate = entityRenderingComponent->getRotation();
			rectangleShape.setRotation(entityAngleRotate);

			rectangleShape.setFillColor(sf::Color::Transparent);
			rectangleShape.setOutlineThickness(1.0f);
			rectangleShape.setOutlineColor(sf::Color::White);

			this->target.draw(rectangleShape);
		}*/
	}
}