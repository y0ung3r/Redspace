#include <string>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CCameraComponent.h"
#include "../Components/CTagComponent.h"

#include "CCameraFactory.h"

CCameraFactory::CCameraFactory(ex::EntityManager& entities, sf::RenderWindow& target)
	: entities(entities), target(target)
{ }

ex::Entity::Id CCameraFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity camera = entities.create();

	CCameraComponent cameraComponent;

	if (!textureKey.empty())
	{
		std::map<std::string, sf::Texture*> mapTextures = CAssetsHelper::getInstance().getMapTextures();
		sf::Texture* mapTexture = mapTextures[textureKey];

		sf::Vector2u mapSizeInPixels = mapTexture->getSize();

		sf::Vector2f mapSizeInCoords;
		mapSizeInCoords.x = static_cast<float>(mapSizeInPixels.x);
		mapSizeInCoords.y = static_cast<float>(mapSizeInPixels.y);

		cameraComponent.setSize(mapSizeInCoords);
	}

	cameraComponent.move(position);
	cameraComponent.setRotation(angleRotate);

	camera.assign<CCameraComponent>(cameraComponent);

	CTagComponent cameraTagComponent(ObjectTypes::Camera);
	camera.assign<CTagComponent>(cameraTagComponent);

	return camera.id();
}
