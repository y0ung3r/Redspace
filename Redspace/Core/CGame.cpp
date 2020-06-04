#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Enums/GameStates.h"
#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Events/CMouseInputEvent.h"
#include "../Components/CInputComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CRotationComponent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CCameraComponent.h"
#include "../Components/CPlayerComponent.h"
#include "../Components/CCollisionComponent.h"
#include "../Systems/CRenderingSystem.h"
#include "../Systems/CCursorSystem.h"
#include "../Systems/CCameraSystem.h"
#include "../Systems/CPlayerInputSystem.h"
#include "../Systems/CPlayerMovementSystem.h"
#include "../Systems/CPlayerRotationSystem.h"
#include "../Systems/CCollisionSystem.h"
#include "../Systems/CMeteoriteSystem.h"
#include "../Systems/CPlayerEndpointMarkerSystem.h"
#include "../Systems/CCircleBorderRenderingSystem.h"

#include "CGame.h"

/* В дальнейшем необходимо изменять состояние игры в процессе геймплея */
GameStates CGame::gameState = GameStates::Unpaused; 

CGame::CGame(sf::RenderWindow& target) : target(target)
{
	CVectorHelper vectorHelper;
	CAssetsHelper::getInstance().configure(true);

	ex::Entity::Id mapId = this->createMap();
	ex::Entity::Id cameraId = this->createCamera();
	ex::Entity::Id playerId = this->createPlayer();

	std::shared_ptr<CRenderingSystem> renderingSystem = this->systems.add<CRenderingSystem>(this->target);
	std::shared_ptr<CCursorSystem> cursorSystem = this->systems.add<CCursorSystem>(this->target);
	std::shared_ptr<CCameraSystem> cameraSystem = this->systems.add<CCameraSystem>(this->target, cameraId, mapId, playerId);
	std::shared_ptr<CPlayerInputSystem> playerInputSystem = this->systems.add<CPlayerInputSystem>(this->target);
	std::shared_ptr<CPlayerMovementSystem> playerMovementSystem = this->systems.add<CPlayerMovementSystem>(vectorHelper, this->target, playerId);
	std::shared_ptr<CPlayerRotationSystem> playerRotationSystem = this->systems.add<CPlayerRotationSystem>(vectorHelper, this->target, playerId);
	std::shared_ptr<CCollisionSystem> collisionSystem = this->systems.add<CCollisionSystem>(this->target);
	std::shared_ptr<CMeteoriteSystem> meteoriteSystem = this->systems.add<CMeteoriteSystem>(this->target, mapId, 50);
	std::shared_ptr<CPlayerEndpointMarkerSystem> playerEndpointMarkerSystem = this->systems.add<CPlayerEndpointMarkerSystem>(this->target);
	std::shared_ptr<CCircleBorderRenderingSystem> circleBorderRenderingSystem = this->systems.add< CCircleBorderRenderingSystem>(this->target);

	this->systems.configure();
}

ex::Entity::Id CGame::createMap()
{
	ex::Entity map = entities.create();

	CRenderingComponent mapRenderingComponent;

	std::map<std::string, sf::Texture*> mapTextures = CAssetsHelper::getInstance().getMapTextures();
	mapRenderingComponent.setTexture(*mapTextures["bg_light"]);
	
	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::IntRect textureArea = sf::IntRect(0, 0, desktopVideoMode.width * 4, desktopVideoMode.height * 4);
	mapRenderingComponent.setTextureRect(textureArea);

	map.assign<CRenderingComponent>(mapRenderingComponent);

	return map.id();
}

ex::Entity::Id CGame::createCamera()
{
	ex::Entity camera = entities.create();

	CCameraComponent cameraComponent;
	camera.assign<CCameraComponent>(cameraComponent);

	return camera.id();
}

ex::Entity::Id CGame::createPlayer()
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

	sf::Vector2u targetSizeInPixels = target.getSize();
	sf::Vector2f targetSizeInCoords = static_cast<sf::Vector2f>(targetSizeInPixels);

	sf::Vector2f playerPosition;
	playerPosition.x = targetSizeInCoords.x / 2.0f;
	playerPosition.y = targetSizeInCoords.y / 2.0f;
	playerRenderingComponent.setPosition(playerPosition);

	player.assign<CRenderingComponent>(playerRenderingComponent);

	CInputComponent playerInputComponent;
	player.assign<CInputComponent>(playerInputComponent);

	CMovementComponent playerMovementComponent;
	player.assign<CMovementComponent>(playerMovementComponent);

	CRotationComponent playerRotationComponent;
	player.assign<CRotationComponent>(playerRotationComponent);

	CCollisionComponent playerCollisionComponent = CCollisionComponent();
	player.assign<CCollisionComponent>(playerCollisionComponent);

	CPlayerComponent playerComponent;
	player.assign<CPlayerComponent>(playerComponent);

	return player.id();
}

void CGame::pollEvent(sf::Event event)
{
	// В будущем вынести этот код в отдельную систему

	while (this->target.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			this->events.emit<CMouseInputEvent>(event.mouseButton);
		}

		if (event.type == sf::Event::Closed)
		{
			this->target.close();
		}
	}
}

void CGame::update(ex::TimeDelta timeDelta)
{
	this->systems.update_all(timeDelta);
}

bool CGame::isGameState(GameStates gameState)
{
	return CGame::gameState == gameState;
}
