#include "CGame.h"

CGame::CGame(sf::RenderWindow& target) : target(target)
{
	ex::Entity::Id mapId = this->createMap();
	ex::Entity::Id cursorId = this->createCursor();
	ex::Entity::Id cameraId = this->createCamera();
	ex::Entity::Id playerId = this->createPlayer();

	std::shared_ptr<CRenderSystem> renderSystem = this->systems.add<CRenderSystem>(this->target);
	std::shared_ptr<CCursorSystem> cursorSystem = this->systems.add<CCursorSystem>(this->target, cursorId);
	std::shared_ptr<CCameraSystem> cameraSystem = this->systems.add<CCameraSystem>(this->target, cameraId, mapId, playerId);
	std::shared_ptr<CPlayerSystem> playerSystem = this->systems.add<CPlayerSystem>(this->target, playerId);

	this->systems.configure();
}

ex::Entity::Id CGame::createMap()
{
	ex::Entity map = entities.create();

	CRenderComponent mapRenderComponent;

	sf::Texture* mapTexture = new sf::Texture();
	mapTexture->loadFromFile("Resources/Textures/Background (black).png");
	mapTexture->setRepeated(true);
	mapRenderComponent.setTexture(*mapTexture);
	
	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::IntRect textureArea = sf::IntRect(0, 0, desktopVideoMode.width * 2, desktopVideoMode.height * 2);
	mapRenderComponent.setTextureRect(textureArea);

	map.assign<CRenderComponent>(mapRenderComponent);

	return map.id();
}

ex::Entity::Id CGame::createCursor()
{
	ex::Entity cursor = entities.create();

	CRenderComponent cursorRenderComponent;

	sf::Texture* cursorTexture = new sf::Texture();
	cursorTexture->loadFromFile("Resources/Sprites/Crosshair.png");
	cursorRenderComponent.setTexture(*cursorTexture);

	sf::Vector2u cursorTextureSizeInPixels = cursorTexture->getSize();
	sf::Vector2f cursorTextureSizeInCoords = static_cast<sf::Vector2f>(cursorTextureSizeInPixels);

	sf::Vector2f cursorOrigin;
	cursorOrigin.x = cursorTextureSizeInPixels.x / 2.0f;
	cursorOrigin.y = cursorTextureSizeInPixels.y / 2.0f;
	cursorRenderComponent.setOrigin(cursorOrigin);

	cursor.assign<CRenderComponent>(cursorRenderComponent);

	return cursor.id();
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

	CRenderComponent playerRenderComponent;

	sf::Texture* playerTexture = new sf::Texture();
	playerTexture->loadFromFile("Resources/Sprites/Player.png");
	playerRenderComponent.setTexture(*playerTexture);

	sf::Vector2u playerTextureSizeInPixels = playerTexture->getSize();
	sf::Vector2f playerTextureSizeInCoords = static_cast<sf::Vector2f>(playerTextureSizeInPixels);

	sf::Vector2f playerOrigin;
	playerOrigin.x = playerTextureSizeInCoords.x / 2.0f;
	playerOrigin.y = playerTextureSizeInCoords.y / 2.0f;
	playerRenderComponent.setOrigin(playerOrigin);

	sf::Vector2u targetSizeInPixels = target.getSize();
	sf::Vector2f targetSizeInCoords = static_cast<sf::Vector2f>(targetSizeInPixels);

	sf::Vector2f playerPosition;
	playerPosition.x = targetSizeInCoords.x / 2.0f;
	playerPosition.y = targetSizeInCoords.y / 2.0f;
	playerRenderComponent.setPosition(playerPosition);

	player.assign<CRenderComponent>(playerRenderComponent);

	CMovementComponent playerMovementComponent(250.0f);
	player.assign<CMovementComponent>(playerMovementComponent);

	return player.id();
}

void CGame::update(ex::TimeDelta timeDelta)
{
	this->systems.update_all(timeDelta);
}