#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Extensions/StringFormat.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CHealthComponent.h"
#include "../Components/CScoreComponent.h"

#include "CUserInterfaceSystem.h"

CUserInterfaceSystem::CUserInterfaceSystem(CGame& game, sf::RenderWindow& target)
	: game(game), target(target)
{ }

void CUserInterfaceSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	float fps = this->game.getFPS();
	CSFMLRenderer* SFMLRenderer = this->game.getSFMLRenderer();

	std::string fpsText = format("FPS: %.2f", fps);
	sf::Vector2f fpsTextPosition = sf::Vector2f(10.0f, 10.0f);
	SFMLRenderer->createTextOnScreen("tahoma", 16, fpsText, fpsTextPosition, sf::Color::White);

	ex::Entity::Id playerId = this->game.getPlayerId();
	ex::Entity player = entities.get(playerId);

	ex::ComponentHandle<CScoreComponent> playerScoreComponent = player.component<CScoreComponent>();
	unsigned int playerScore = playerScoreComponent->getScore();

	std::string scoreText = format("%08d", playerScore);
	sf::Vector2f scoreTextPosition = sf::Vector2f(10.0f, 30.0f);
	SFMLRenderer->createTextOnScreen("kenVector", 18, scoreText, scoreTextPosition, sf::Color::White);

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CHealthComponent> entityHealthComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityHealthComponent))
	{
		ObjectTypes entityTag = entityTagComponent->getTag();

		// Оптимизировать в будущем!
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
			SFMLRenderer->createGameBox(HPBarSize, HPBarPosition, sf::Color::Transparent, thickness, HPBarOutlineColor);

			float entityHealth = entityHealthComponent->getHealth();
			float entityMaxHealth = entityHealthComponent->getMaxHealth();
			sf::Vector2f HPBarLineSize(entityHealth * HPBarSize.x / entityMaxHealth, HPBarSize.y);

			sf::Color HPBarLineBackgroundColor = sf::Color(255, 0, 0, 150);
			SFMLRenderer->createGameBox(HPBarLineSize, HPBarPosition, HPBarLineBackgroundColor, 0.0f);

			std::string healthText = format("%.1f HP", entityHealth);
			int healthTextLength = healthText.length();

			sf::Vector2f HPTextPosition;
			HPBarPosition.x = HPBarPosition.x + 5.0f;
			HPBarPosition.y = HPBarPosition.y;

			SFMLRenderer->createGameText("kenVector", 12, healthText, HPBarPosition);
		}
	}
}
