#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Components/CCameraComponent.h"
#include "../Components/CRenderingComponent.h"

#include "CCameraSystem.h"

CCameraSystem::CCameraSystem(sf::RenderWindow& target, ex::Entity::Id cameraId, ex::Entity::Id mapId, ex::Entity::Id objectId) 
	: target(target), cameraId(cameraId), mapId(mapId), objectId(objectId)
{ }

void CCameraSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity camera = entities.get(this->cameraId);
	ex::Entity map = entities.get(this->mapId);
	ex::Entity object = entities.get(this->objectId);

	ex::ComponentHandle<CCameraComponent> cameraComponent = camera.component<CCameraComponent>();
	ex::ComponentHandle<CRenderingComponent> mapRenderingComponent = map.component<CRenderingComponent>();
	ex::ComponentHandle<CRenderingComponent> objectRenderingComponent = object.component<CRenderingComponent>();

	sf::Vector2u targetSize = this->target.getSize();

	float newSizeX = (float)targetSize.x;
	float newSizeY = (float)targetSize.y;

	cameraComponent->setSize(newSizeX, newSizeY);

	float cameraSizeX = newSizeX / 2.0f;
	float cameraSizeY = newSizeY / 2.0f;

	sf::IntRect mapSize = mapRenderingComponent->getTextureRect();

	sf::Vector2f objectPosition = objectRenderingComponent->getPosition();
	cameraComponent->setCenter(objectPosition);

	bool isReachedLeft = objectPosition.x - cameraSizeX < mapSize.left;
	bool isReachedTop = objectPosition.y - cameraSizeY < mapSize.top;
	bool isReachedRight = objectPosition.x + cameraSizeX > mapSize.width;
	bool isReachedBottom = objectPosition.y + cameraSizeY > mapSize.height;

	if (isReachedLeft)
	{
		cameraComponent->setCenter(cameraSizeX, objectPosition.y);
	}

	if (isReachedTop)
	{
		cameraComponent->setCenter(objectPosition.x, cameraSizeY);
	}

	if (isReachedLeft && isReachedTop)
	{
		cameraComponent->setCenter(cameraSizeX, cameraSizeY);
	}

	if (isReachedRight)
	{
		cameraComponent->setCenter(mapSize.width - cameraSizeX, objectPosition.y);
	}

	if (isReachedBottom)
	{
		cameraComponent->setCenter(objectPosition.x, mapSize.height - cameraSizeY);
	}

	if (isReachedRight && isReachedBottom)
	{
		cameraComponent->setCenter(mapSize.width - cameraSizeX, mapSize.height - cameraSizeY);
	}

	if (isReachedLeft && isReachedBottom)
	{
		cameraComponent->setCenter(cameraSizeX, mapSize.height - cameraSizeY);
	}

	if (isReachedRight && isReachedTop)
	{
		cameraComponent->setCenter(mapSize.width - cameraSizeX, cameraSizeY);
	}

	CCameraComponent instance = *cameraComponent.get();
	this->target.setView(instance);
}