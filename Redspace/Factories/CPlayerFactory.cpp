#include <string>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CWeaponComponent.h"
#include "../Components/CHealthComponent.h"
#include "../Components/CScoreComponent.h"

#include "CPlayerFactory.h"

CPlayerFactory::CPlayerFactory(ex::EntityManager& entities, sf::RenderWindow& target)
	: entities(entities), target(target)
{ }

ex::Entity::Id CPlayerFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity player = entities.create();

	CRenderingComponent playerRenderingComponent;

	sf::Texture* playerTexture = CAssetsHelper::getInstance().getPlayerTexture();
	playerRenderingComponent.setTexture(*playerTexture);

	sf::Vector2u playerTextureSizeInPixels = playerTexture->getSize();
	sf::Vector2f playerTextureSizeInCoords = static_cast<sf::Vector2f>(playerTextureSizeInPixels);

	sf::Vector2f playerOrigin;
	playerOrigin.x = playerTextureSizeInCoords.x / 2.0f;
	playerOrigin.y = playerTextureSizeInCoords.y / 2.0f;
	playerRenderingComponent.setOrigin(playerOrigin);

	sf::Vector2f nullVector = sf::Vector2f();
	bool isPositionEmpty = position == nullVector;

	if (isPositionEmpty)
	{
		sf::Vector2u targetSizeInPixels = target.getSize();
		sf::Vector2f targetSizeInCoords = static_cast<sf::Vector2f>(targetSizeInPixels);

		sf::Vector2f playerPosition;
		playerPosition.x = targetSizeInCoords.x / 2.0f;
		playerPosition.y = targetSizeInCoords.y / 2.0f;
		playerRenderingComponent.setPosition(playerPosition);
	}
	else
	{
		playerRenderingComponent.setPosition(position);
	}

	player.assign<CRenderingComponent>(playerRenderingComponent);

	CTagComponent playerTagComponent(ObjectTypes::Player);
	player.assign<CTagComponent>(playerTagComponent);

	CMovementComponent* playerMovementComponent = new CMovementComponent(250.0f);
	player.assign<CMovementComponent*>(playerMovementComponent);

	CWeaponComponent playerWeaponComponent(15.0f);
	player.assign<CWeaponComponent>(playerWeaponComponent);

	CHealthComponent playerHealthComponent(9999999999.0f);
	player.assign<CHealthComponent>(playerHealthComponent);

	CScoreComponent playerScoreComponent;
	player.assign<CScoreComponent>(playerScoreComponent);

	return player.id();
}
