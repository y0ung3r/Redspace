#include <sstream>
#include <iomanip>
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
#include "../Factories/CEnemyFactory.h"
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
#include "../Systems/CEnemySystem.h"
#include "../Systems/CHealthSystem.h"

#include "CGame.h"

CGame::CGame(sf::RenderWindow& target)
	: target(target)
{
	this->target.setFramerateLimit(120);
	this->target.setVerticalSyncEnabled(false);

	this->events.subscribe<ex::EntityDestroyedEvent>(*this);

	CAssetsHelper::getInstance().configure(true);
	CVectorHelper vectorHelper;

	this->mapFactory = new CMapFactory(this->entities, this->target);
	this->mapId = mapFactory->create("bg_light");

	this->cameraFactory = new CCameraFactory(this->entities, this->target);
	this->cameraId = cameraFactory->create();

	this->playerFactory = new CPlayerFactory(this->entities, this->target);
	this->playerId = playerFactory->create("player");

	this->bulletFactory = new CBulletFactory(vectorHelper, this->entities, this->target);
	this->enemyFactory = new CEnemyFactory(this->entities, this->target);
	
	std::shared_ptr<CRenderingSystem> renderingSystem = this->systems.add<CRenderingSystem>(this->target);
	std::shared_ptr<CCursorSystem> cursorSystem = this->systems.add<CCursorSystem>(this->target);
	std::shared_ptr<CCameraSystem> cameraSystem = this->systems.add<CCameraSystem>(*this, this->target);
	std::shared_ptr<CCollisionTrackingSystem> collisionTrackingSystem = this->systems.add<CCollisionTrackingSystem>(this->target);
	std::shared_ptr<CMouseHoverTrackingSystem> mouseHoverTrackingSystem = this->systems.add<CMouseHoverTrackingSystem>(this->target);
	std::shared_ptr<CLostVisibilityTrackingSystem> lostVisibilityTrackingSystem = this->systems.add<CLostVisibilityTrackingSystem>(*this, this->target);
	std::shared_ptr<CMovementSystem> movementSystem = this->systems.add<CMovementSystem>(*this, vectorHelper, this->target);
	std::shared_ptr<CBulletSystem> bulletSystem = this->systems.add<CBulletSystem>(this->target);
	std::shared_ptr<CShootingSystem> shootingSystem = this->systems.add<CShootingSystem>(*this, vectorHelper, *this->bulletFactory, this->target);
	std::shared_ptr<CEnemySystem> enemySystem = this->systems.add<CEnemySystem>(*this, *this->enemyFactory, this->target, 25);
	std::shared_ptr<CHealthSystem> healthSystem = this->systems.add<CHealthSystem>(this->target);

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

void CGame::update(ex::TimeDelta timeDelta, sf::Time elapsedTime)
{
	this->fps = 1.0f / elapsedTime.asSeconds();
	this->systems.update_all(timeDelta);

	// Позже перенести в правильное место!
	sf::Font font = CAssetsHelper::getInstance().getFonts().at("tahoma");

	std::ostringstream stream;

	stream << "FPS: ";
	stream << std::fixed;
	stream << std::setprecision(2);
	stream << this->fps;

	std::string line = stream.str();
	sf::Text text(line, font, 16);

	sf::View targetView = this->target.getView();
	sf::Vector2f targetCenter = targetView.getCenter();
	sf::Vector2f targetSize = targetView.getSize();

	float left = targetCenter.x - targetSize.x / 2 + 10.0f;
	float top = targetCenter.y - targetSize.y / 2 + 10.0f;
	text.setPosition(left, top);
	
	this->target.draw(text);
}

float CGame::getFPS()
{
	return this->fps;
}

ex::Entity::Id CGame::getCameraId()
{
	return this->cameraId;
}

ex::Entity::Id CGame::getMapId()
{
	return this->mapId;
}

ex::Entity::Id CGame::getPlayerId()
{
	return this->playerId;
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

void CGame::receive(const ex::EntityDestroyedEvent& entityDestroyedEvent)
{
	ex::Entity destroyedObject = entityDestroyedEvent.entity;

	if (!destroyedObject)
	{
		return;
	}

	ex::ComponentHandle<CTagComponent> destroyedObjectTagComponent = destroyedObject.component<CTagComponent>();
	ObjectTypes destroyedObjectTag = destroyedObjectTagComponent->getTag();

	if (destroyedObjectTag == ObjectTypes::Player)
	{
		this->playerId = this->playerFactory->create("player");
	}
}