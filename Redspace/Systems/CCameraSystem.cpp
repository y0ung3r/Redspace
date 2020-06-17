#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Components/CCameraComponent.h"
#include "../Components/CRenderingComponent.h"

#include "CCameraSystem.h"

CCameraSystem::CCameraSystem(CGame& game, sf::RenderWindow& target)
	: game(game), target(target)
{ }

void CCameraSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity::Id cameraId = this->game.getCameraId();
	ex::Entity camera = entities.get(cameraId);

	ex::Entity::Id mapId = this->game.getMapId();
	ex::Entity map = entities.get(mapId);

	ex::Entity::Id playerId = this->game.getPlayerId();
	ex::Entity player = entities.get(playerId);

	ex::ComponentHandle<CCameraComponent> cameraComponent = camera.component<CCameraComponent>();
	ex::ComponentHandle<CRenderingComponent> mapRenderingComponent = map.component<CRenderingComponent>();
	ex::ComponentHandle<CRenderingComponent> playerRenderingComponent = player.component<CRenderingComponent>();

	sf::Vector2u targetSize = this->target.getSize();

	float newSizeX = (float)targetSize.x;
	float newSizeY = (float)targetSize.y;

	cameraComponent->setSize(newSizeX, newSizeY);

	float cameraSizeX = newSizeX / 2.0f;
	float cameraSizeY = newSizeY / 2.0f;

	sf::IntRect mapSize = mapRenderingComponent->getTextureRect();

	sf::Vector2f playerPosition = playerRenderingComponent->getPosition();
	cameraComponent->setCenter(playerPosition);

	bool isReachedLeft = playerPosition.x - cameraSizeX < mapSize.left;
	bool isReachedTop = playerPosition.y - cameraSizeY < mapSize.top;
	bool isReachedRight = playerPosition.x + cameraSizeX > mapSize.width;
	bool isReachedBottom = playerPosition.y + cameraSizeY > mapSize.height;

	if (isReachedLeft)
	{
		cameraComponent->setCenter(cameraSizeX, playerPosition.y);
	}

	if (isReachedTop)
	{
		cameraComponent->setCenter(playerPosition.x, cameraSizeY);
	}

	if (isReachedLeft && isReachedTop)
	{
		cameraComponent->setCenter(cameraSizeX, cameraSizeY);
	}

	if (isReachedRight)
	{
		cameraComponent->setCenter(mapSize.width - cameraSizeX, playerPosition.y);
	}

	if (isReachedBottom)
	{
		cameraComponent->setCenter(playerPosition.x, mapSize.height - cameraSizeY);
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