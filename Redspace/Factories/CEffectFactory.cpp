#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Components/CRenderingComponent.h"

#include "CEffectFactory.h"

CEffectFactory::CEffectFactory(ex::EntityManager& entities, sf::RenderWindow& target)
	: entities(entities), target(target)
{ }

ex::Entity::Id CEffectFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity effect = entities.create();

	CRenderingComponent effectRenderingComponent;

	std::map<std::string, sf::Texture*> effectTextures = CAssetsHelper::getInstance().getBulletsTextures(); // Ёффекты переместить в отдельный список!
	sf::Texture* effectTexture = effectTextures[textureKey];
	effectRenderingComponent.setTexture(*effectTexture);

	sf::Vector2u effectTextureSizeInPixels = effectTexture->getSize();
	sf::Vector2f effectTextureSizeInCoords = static_cast<sf::Vector2f>(effectTextureSizeInPixels);

	sf::Vector2f effectOrigin;
	effectOrigin.x = effectTextureSizeInCoords.x / 2.0f;
	effectOrigin.y = effectTextureSizeInCoords.y / 2.0f;
	effectRenderingComponent.setOrigin(effectOrigin);

	effectRenderingComponent.setScale(0.75f, 0.75f);

	effectRenderingComponent.setRotation(angleRotate);

	effectRenderingComponent.setPosition(position);

	effect.assign<CRenderingComponent>(effectRenderingComponent);

	return effect.id();
}
