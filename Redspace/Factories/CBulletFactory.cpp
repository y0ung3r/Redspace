#include <string>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CBulletMovementComponent.h"

#include "CBulletFactory.h"

CBulletFactory::CBulletFactory(CVectorHelper& vectorHelper, ex::EntityManager& entities, sf::RenderWindow& target)
	: vectorHelper(vectorHelper), entities(entities), target(target)
{ }

ex::Entity::Id CBulletFactory::create(std::string textureKey, sf::Vector2f position, float angleRotate)
{
	ex::Entity bullet = entities.create();

	CRenderingComponent bulletRenderingComponent;

	std::map<std::string, sf::Texture*> bulletTextures = CAssetsHelper::getInstance().getBulletsTextures();
	sf::Texture* bulletTexture = bulletTextures[textureKey];
	bulletRenderingComponent.setTexture(*bulletTexture);

	sf::Vector2u bulletTextureSizeInPixels = bulletTexture->getSize();
	sf::Vector2f bulletTextureSizeInCoords = static_cast<sf::Vector2f>(bulletTextureSizeInPixels);

	sf::Vector2f bulletOrigin;
	bulletOrigin.x = bulletTextureSizeInCoords.x / 2.0f;
	bulletOrigin.y = bulletTextureSizeInCoords.y / 2.0f;
	bulletRenderingComponent.setOrigin(bulletOrigin);

	bulletRenderingComponent.setScale(0.75f, 0.75f);

	bulletRenderingComponent.setRotation(angleRotate);

	CTagComponent bulletTagComponent(ObjectTypes::Bullet);
	bullet.assign<CTagComponent>(bulletTagComponent);

	float length = -1.0f * vectorHelper.getLength(position);
	float angleRotateInRadians = angleRotate * (PI / 180.0f);

	sf::Vector2f difference;
	difference.x = length * std::cosf(angleRotateInRadians);
	difference.y = length * std::sinf(angleRotateInRadians);

	sf::Vector2f direction = vectorHelper.getOrt(difference);

	bulletRenderingComponent.setPosition(position + bulletTextureSizeInCoords.x * direction);

	bullet.assign<CRenderingComponent>(bulletRenderingComponent);

	CMovementComponent* bulletMovementComponent = new CBulletMovementComponent(1000.0f, direction);
	bullet.assign<CMovementComponent*>(bulletMovementComponent);

	return bullet.id();
}
