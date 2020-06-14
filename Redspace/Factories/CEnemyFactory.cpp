#include <map>
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
#include "../Components/ÑEndpointMovementComponent.h"

#include "CEnemyFactory.h"

CEnemyFactory::CEnemyFactory(ex::EntityManager& entities, sf::RenderWindow& target)
	: entities(entities), target(target)
{ }

ex::Entity::Id CEnemyFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity enemy = entities.create();

	CRenderingComponent enemyRenderingComponent;

	std::map<std::string, sf::Texture*> enemiesTextures = CAssetsHelper::getInstance().getEnemiesTextures();
	sf::Texture* enemyTexture = enemiesTextures["enemy"];
	enemyRenderingComponent.setTexture(*enemyTexture);

	sf::Vector2u enemyTextureSizeInPixels = enemyTexture->getSize();
	sf::Vector2f enemyTextureSizeInCoords = static_cast<sf::Vector2f>(enemyTextureSizeInPixels);

	sf::Vector2f enemyOrigin;
	enemyOrigin.x = enemyTextureSizeInCoords.x / 2.0f;
	enemyOrigin.y = enemyTextureSizeInCoords.y / 2.0f;
	enemyRenderingComponent.setOrigin(enemyOrigin);

	enemyRenderingComponent.setPosition(position);

	enemy.assign<CRenderingComponent>(enemyRenderingComponent);

	CTagComponent enemyTagComponent(ObjectTypes::Enemy);
	enemy.assign<CTagComponent>(enemyTagComponent);
	
	CMovementComponent* enemyMovementComponent = new ÑEndpointMovementComponent(350.0f, position);
	enemy.assign<CMovementComponent*>(enemyMovementComponent);

	CWeaponComponent enemyWeaponComponent(15.0f);
	enemy.assign<CWeaponComponent>(enemyWeaponComponent);

	CHealthComponent enemyHealthComponent(100.0f);
	enemy.assign<CHealthComponent>(enemyHealthComponent);

	return enemy.id();
}
