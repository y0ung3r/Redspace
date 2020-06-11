#include <string>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"

#include "CMapFactory.h"

CMapFactory::CMapFactory(ex::EntityManager& entities, sf::RenderWindow& target)
	: entities(entities), target(target)
{ }

ex::Entity::Id CMapFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity map = entities.create();

	CRenderingComponent mapRenderingComponent;

	std::map<std::string, sf::Texture*> mapTextures = CAssetsHelper::getInstance().getMapTextures();
	mapRenderingComponent.setTexture(*mapTextures[textureKey]);

	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::IntRect textureArea = sf::IntRect(0, 0, desktopVideoMode.width * 4, desktopVideoMode.height * 4);
	mapRenderingComponent.setTextureRect(textureArea);

	mapRenderingComponent.setPosition(position);
	mapRenderingComponent.setRotation(angleRotate);

	map.assign<CRenderingComponent>(mapRenderingComponent);

	CTagComponent mapTagComponent(ObjectTypes::Map);
	map.assign<CTagComponent>(mapTagComponent);

	return map.id();
}
