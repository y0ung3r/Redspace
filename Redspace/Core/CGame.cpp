#include "CGame.h"

/* В дальнейшем необходимо изменять состояние игры в процессе геймплея */
GameStates CGame::gameState = GameStates::Paused; 

CGame::CGame(sf::RenderWindow& target) : target(target)
{
	CVectorHelper vectorHelper;
	CAssetsHelper::getInstance().configure(true);

	ex::Entity::Id mapId = this->createMap();
	ex::Entity::Id cameraId = this->createCamera();
	ex::Entity::Id playerId = this->createPlayer();

	std::shared_ptr<CRenderSystem> renderSystem = this->systems.add<CRenderSystem>(this->target);
	std::shared_ptr<CCursorSystem> cursorSystem = this->systems.add<CCursorSystem>(this->target);
	std::shared_ptr<CCameraSystem> cameraSystem = this->systems.add<CCameraSystem>(this->target, cameraId, mapId, playerId);
	std::shared_ptr<CPlayerSystem> playerSystem = this->systems.add<CPlayerSystem>(vectorHelper, this->target, playerId);
	std::shared_ptr<CMeteoriteSystem> meteoriteSystem = this->systems.add<CMeteoriteSystem>(this->target, mapId, 35);
	std::shared_ptr<CCollisionSystem> collisionSystem = this->systems.add<CCollisionSystem>(this->target);

	this->systems.configure();
}

ex::Entity::Id CGame::createMap()
{
	ex::Entity map = entities.create();

	CRenderComponent mapRenderComponent;

	std::vector<sf::Texture*> mapTextures = CAssetsHelper::getInstance().getMapTextures();
	mapRenderComponent.setTexture(*mapTextures[3]);
	
	sf::VideoMode desktopVideoMode = sf::VideoMode::getDesktopMode();
	sf::IntRect textureArea = sf::IntRect(0, 0, desktopVideoMode.width * 2, desktopVideoMode.height * 2);
	mapRenderComponent.setTextureRect(textureArea);

	map.assign<CRenderComponent>(mapRenderComponent);

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

	CRenderComponent playerRenderComponent;

	sf::Texture* playerTexture = CAssetsHelper::getInstance().getPlayerTexture();
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

	CMovementComponent playerMovementComponent(0.0f, 350.0f);
	player.assign<CMovementComponent>(playerMovementComponent);

	CCollisionComponent playerCollisionComponent;
	player.assign<CCollisionComponent>(playerCollisionComponent);

	CPlayerComponent playerComponent;
	player.assign<CPlayerComponent>(playerComponent);

	return player.id();
}

void CGame::update(ex::TimeDelta timeDelta)
{
	this->systems.update_all(timeDelta);
}

bool CGame::isGameState(GameStates gameState)
{
	return CGame::gameState == gameState;
}
