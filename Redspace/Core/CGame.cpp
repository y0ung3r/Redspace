#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/GameStates.h"
#include "../Enums/ObjectTypes.h"
#include "../Factories/CMapFactory.h"
#include "../Factories/CCameraFactory.h"
#include "../Factories/CPlayerFactory.h"
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
	CAssetsHelper::getInstance().configure(true);

	CVectorHelper vectorHelper;

	IObjectFactory* mapFactory = new CMapFactory(this->entities, this->target);
	ex::Entity::Id mapId = mapFactory->create("bg_light");

	IObjectFactory* cameraFactory = new CCameraFactory(this->entities, this->target);
	ex::Entity::Id cameraId = cameraFactory->create();

	IObjectFactory* playerFactory = new CPlayerFactory(this->entities, this->target);
	ex::Entity::Id playerId = playerFactory->create("player");

	IObjectFactory* bulletFactory = new CBulletFactory(vectorHelper, this->entities, this->target);

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