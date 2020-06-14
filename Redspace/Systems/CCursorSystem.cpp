#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Core/CGame.h"
#include "../Enums/GameStates.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CGameStateChangedEvent.h"
#include "../Events/CMouseHoverEvent.h"
#include "../Events/CMouseExitEvent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"

#include "CCursorSystem.h"

CCursorSystem::CCursorSystem(sf::RenderWindow& target)
	: target(target)
{
	this->cursors = CAssetsHelper::getInstance().getCursors();
}

void CCursorSystem::configure(ex::EventManager& events)
{
	events.subscribe<CGameStateChangedEvent>(*this);
	events.subscribe<CMouseHoverEvent>(*this);
	events.subscribe<CMouseExitEvent>(*this);
}

void CCursorSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	this->target.setMouseCursor(*this->cursor);
}

void CCursorSystem::receive(const CGameStateChangedEvent& gameStateChangedEvent)
{
	GameStates gameState = gameStateChangedEvent.getGameState();

	switch (gameState)
	{
	case Paused:
		this->cursor = this->cursors["csr_ship"];
		break;

	case Unpaused:
		this->cursor = this->cursors["csr_crosshair"];
		break;
	}
}

void CCursorSystem::receive(const CMouseHoverEvent& mouseHoverEvent)
{
	ex::Entity hoveredObject = mouseHoverEvent.getHoveredObject();

	if (!hoveredObject)
	{
		return;
	}

	ex::ComponentHandle<CTagComponent> hoveredObjectTagComponent = hoveredObject.component<CTagComponent>();

	ObjectTypes hoveredObjectTag = hoveredObjectTagComponent->getTag();

	switch (hoveredObjectTag)
	{
	case Thing:
		this->cursor = this->cursors["csr_crosshair_hover"];
		break;

	case Enemy:
		this->cursor = this->cursors["csr_crosshair_attack"];
		break;

	default:
		this->cursor = this->cursors["csr_crosshair"];
		break;
	}
}

void CCursorSystem::receive(const CMouseExitEvent& mouseExitEvent)
{
	this->cursor = this->cursors["csr_crosshair"];
}