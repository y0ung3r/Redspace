#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Extensions/StringFormat.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CHealthComponent.h"

#include "CUserInterfaceSystem.h"

CUserInterfaceSystem::CUserInterfaceSystem(CGame& game, sf::RenderWindow& target)
	: game(game), target(target)
{ }

void CUserInterfaceSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	float fps = game.getFPS();
	CSFMLRenderer* sfmlRenderer = this->game.getSFMLRenderer();

	std::string fpsText = format("FPS: %.2f", fps);
	sf::Vector2f fpsTextPosition = sf::Vector2f(10.0f, 10.0f);
	sfmlRenderer->createTextOnScreen("tahoma", 16.0f, fpsText, fpsTextPosition, sf::Color::White);

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CHealthComponent> entityHealthComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityHealthComponent))
	{
		ObjectTypes entityTag = entityTagComponent->getTag();

		if (entityTag == ObjectTypes::Enemy)
		{
			sf::Vector2u entityTextureSizeInPixels = entityRenderingComponent->getTexture()->getSize();
			sf::Vector2f entityTextureSizeInCoords = static_cast<sf::Vector2f>(entityTextureSizeInPixels);
			sf::Vector2f entityPosition = entityRenderingComponent->getPosition();

			float thickness = 2.0f;
			sf::Vector2f HPBarSize(entityTextureSizeInCoords.x + 14.0f + thickness, 14.0f + thickness);

			sf::Vector2f HPBarPosition;
			HPBarPosition.x = entityPosition.x - entityTextureSizeInCoords.x / 2.0f - 14.0f;
			HPBarPosition.y = entityPosition.y - entityTextureSizeInCoords.y / 2.0f - (HPBarSize.y + 10.0f + thickness);

			sf::Color HPBarOutlineColor = sf::Color(0, 0, 0, 100);
			sfmlRenderer->createGameRoundedBox(HPBarSize, HPBarPosition, 5.0f, sf::Color::Transparent, thickness, HPBarOutlineColor);

			float health = entityHealthComponent->getHealth();
			float maxHealth = entityHealthComponent->getMaxHealth();
			sf::Vector2f HPBarLineSize(health * HPBarSize.x / maxHealth, HPBarSize.y);

			sf::Color HPBarLineBackgroundColor = sf::Color(255, 0, 0, 100);
			sfmlRenderer->createGameRoundedBox(HPBarLineSize, HPBarPosition, 5.0f, HPBarLineBackgroundColor, 0.0f);

			std::string healthText = format("%.2f HP", health);
			int healthTextLength = healthText.length();

			sf::Vector2f HPTextPosition;
			HPBarPosition.x = HPBarPosition.x + 5.0f;
			HPBarPosition.y = HPBarPosition.y;

			sfmlRenderer->createGameText("kenVector", 12, healthText, HPBarPosition);
		}
	}
}
