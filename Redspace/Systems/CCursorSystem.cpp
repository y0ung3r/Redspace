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
	if (this->gameState == GameStates::Unpaused)
	{
		this->cursor = this->cursors["csr_crosshair"];

		if (this->hoveredObject && isCursorHover)
		{
			ex::ComponentHandle<CTagComponent> hoveredObjectTagComponent = this->hoveredObject.component<CTagComponent>();
			ObjectTypes hoveredObjectTag = hoveredObjectTagComponent->getTag();

			switch (hoveredObjectTag)
			{
			case Thing:
			case Meteorite:
				this->cursor = this->cursors["csr_crosshair_hover"];
				break;

			case Enemy:
				this->cursor = this->cursors["csr_crosshair_attack"];
				break;
			}
		}
	}
	else if (this->gameState == GameStates::Paused)
	{
		this->cursor = this->cursors["csr_ship"];
	}

	if (this->cursor)
	{
		this->target.setMouseCursor(*this->cursor);
	}
}

void CCursorSystem::receive(const CGameStateChangedEvent& gameStateChangedEvent)
{
	this->gameState = gameStateChangedEvent.getGameState();
}

void CCursorSystem::receive(const CMouseHoverEvent& mouseHoverEvent)
{
	this->isCursorHover = true;
	this->hoveredObject = mouseHoverEvent.getHoveredObject();
}

void CCursorSystem::receive(const CMouseExitEvent& mouseExitEvent)
{
	this->isCursorHover = false;
}