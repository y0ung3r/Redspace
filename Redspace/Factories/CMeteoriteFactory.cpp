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
#include "../Components/CViewRadiusComponent.h"

#include "CMeteoriteFactory.h"

CMeteoriteFactory::CMeteoriteFactory(ex::EntityManager& entities, sf::RenderWindow& target)
	: entities(entities), target(target)
{ }

ex::Entity::Id CMeteoriteFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity meteorite = entities.create();

	CRenderingComponent meteoriteRenderingComponent;

	std::map<std::string, sf::Texture*> meteoritesTextures = CAssetsHelper::getInstance().getMeteoritesTextures();
	sf::Texture* meteoriteTexture = meteoritesTextures[textureKey];
	meteoriteRenderingComponent.setTexture(*meteoriteTexture);

	sf::Vector2u meteoriteTextureSizeInPixels = meteoriteTexture->getSize();
	sf::Vector2f meteoriteTextureSizeInCoords = static_cast<sf::Vector2f>(meteoriteTextureSizeInPixels);

	sf::Vector2f meteoriteOrigin;
	meteoriteOrigin.x = meteoriteTextureSizeInCoords.x / 2.0f;
	meteoriteOrigin.y = meteoriteTextureSizeInCoords.y / 2.0f;
	meteoriteRenderingComponent.setOrigin(meteoriteOrigin);

	meteoriteRenderingComponent.setPosition(position);

	meteorite.assign<CRenderingComponent>(meteoriteRenderingComponent);

	CTagComponent meteoriteTagComponent(ObjectTypes::Meteorite);
	meteorite.assign<CTagComponent>(meteoriteTagComponent);

	CHealthComponent meteoriteHealthComponent(50.0f);
	meteorite.assign<CHealthComponent>(meteoriteHealthComponent);

	return meteorite.id();
}
