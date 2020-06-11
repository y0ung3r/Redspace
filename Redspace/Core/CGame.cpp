#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/GameStates.h"
#include "../Enums/ObjectTypes.h"
#include "../Factories/CBulletFactory.h"
#include "../Events/CSingleMouseInputEvent.h"
#include "../Events/CSingleKeyInputEvent.h"
#include "../Events/CGameStateChangedEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CCameraComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CWeaponComponent.h"
#include "../Systems/CRenderingSystem.h"
#include "../Systems/CCursorSystem.h"
#include "../Systems/CCameraSystem.h"
#include "../Systems/CCollisionTrackingSystem.h"
#include "../Systems/CMouseHoverTrackingSystem.h"
#include "../Systems/CLostVisibilityTrackingSystem.h"
#include "../Systems/CMovementSystem.h"
#include "../Systems/CBulletSystem.h"
#include "../Systems/CShootingSystem.h"

#include "CGame.h"

CGame::CGame(sf::RenderWindow& target)
	: target(target)
{
	CVectorHelper vectorHelper;
	CAssetsHelper::getInstance().configure(true);

	IObjectFactory* bulletFactory = new CBulletFactory(vectorHelper, this->entities, this->target);

	ex::Entity::Id mapId = this->createMap();
	ex::Entity::Id cameraId = this->createCamera();
	ex::Entity::Id playerId = this->createPlayer();

	std::shared_ptr<CRenderingSystem> renderingSystem = this->systems.add<CRenderingSystem>(this->target);
	std::shared_ptr<CCursorSystem> cursorSystem = this->systems.add<CCursorSystem>(this->target);
	std::shared_ptr<CCameraSystem> cameraSystem = this->systems.add<CCameraSystem>(this->target, cameraId, mapId, playerId);
	std::shared_ptr<CCollisionTrackingSystem> collisionTrackingSystem = this->systems.add<CCollisionTrackingSystem>(this->target);
	std::shared_ptr<CMouseHoverTrackingSystem> mouseHoverTrackingSystem = this->systems.add<CMouseHoverTrackingSystem>(this->target);
	std::shared_ptr<CLostVisibilityTrackingSystem> lostVisibilityTrackingSystem = this->systems.add<CLostVisibilityTrackingSystem>(this->target, mapId);
	std::shared_ptr<CMovementSystem> MovementSystem = this->systems.add<CMovementSystem>(vectorHelper, this->target);
	std::shared_ptr<CBulletSystem> bulletSystem = this->systems.add<CBulletSystem>(this->target);
	std::shared_ptr<CShootingSystem> shootingSystem = this->systems.add<CShootingSystem>(*bulletFactory, this->target);

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

	CTagComponent mapTagComponent(ObjectTypes::Map);
	map.assign<CTagComponent>(mapTagComponent);

	return map.id();
}

ex::Entity::Id CGame::createCamera()
{
	ex::Entity camera = entities.create();

	CCameraComponent cameraComponent;
	camera.assign<CCameraComponent>(cameraComponent);

	CTagComponent cameraTagComponent(ObjectTypes::Camera);
	camera.assign<CTagComponent>(cameraTagComponent);

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

	CTagComponent playerTagComponent(ObjectTypes::Player);
	player.assign<CTagComponent>(playerTagComponent);

	CMovementComponent* playerMovementComponent = new CMovementComponent(300.0f);
	player.assign<CMovementComponent*>(playerMovementComponent);

	CWeaponComponent playerWeaponComponent(25.0f);
	player.assign<CWeaponComponent>(playerWeaponComponent);

	return player.id();
}

void CGame::pollEvent(sf::Event event)
{
	while (this->target.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			this->events.emit<CSingleMouseInputEvent>(event.type, event.mouseButton);
			break;

		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
			this->events.emit<CSingleKeyInputEvent>(event.type, event.key);
			break;

		case sf::Event::LostFocus:
			this->setGameState(GameStates::Paused);
			break;

		case sf::Event::Closed:
			this->target.close();
			break;
		}
	}
}

void CGame::update(ex::TimeDelta timeDelta)
{
	this->systems.update_all(timeDelta);
}

void CGame::setGameState(GameStates gameState)
{
	this->gameState = gameState;

	this->events.emit<CGameStateChangedEvent>(this->gameState);
}

bool CGame::isGameState(GameStates gameState)
{
	return this->gameState == gameState;
}

const sf::Vector2f& CGame::getMousePositionInCoords(sf::RenderWindow& target)
{
	sf::Vector2i mousePositionInPixels = sf::Mouse::getPosition(target);
	sf::Vector2f mousePositionInCoords = target.mapPixelToCoords(mousePositionInPixels);

	return mousePositionInCoords;
}