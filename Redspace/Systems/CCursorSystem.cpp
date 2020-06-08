#include <map>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Core/CGame.h"
#include "../Enums/GameStates.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CCircleBorderComponent.h"
#include "../Components/CEnemyComponent.h"

#include "CCursorSystem.h"

CCursorSystem::CCursorSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CCursorSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	std::map<std::string, sf::Cursor*> cursors = CAssetsHelper::getInstance().getCursors();

	bool mustUseGameStates = true;

	ex::ComponentHandle<CRenderingComponent> objectRenderingComponent;
	ex::ComponentHandle<CCircleBorderComponent> nearbyObjectCircleBorderComponent;

	for (ex::Entity entity : entities.entities_with_components(objectRenderingComponent, nearbyObjectCircleBorderComponent))
	{
		sf::Vector2i mousePositionInPixels = sf::Mouse::getPosition(this->target);
		sf::Vector2f mousePositionInCoords = this->target.mapPixelToCoords(mousePositionInPixels);

		sf::FloatRect objectGlobalBounds = objectRenderingComponent->getGlobalBounds();

		if (objectGlobalBounds.contains(mousePositionInCoords))
		{
			mustUseGameStates = false;

			sf::Cursor* crosshair = (entity.has_component<CEnemyComponent>()) ? cursors["csr_crosshair_attack"] : cursors["csr_crosshair_intersect"];
			this->target.setMouseCursor(*crosshair);
		}
	}

	if (mustUseGameStates)
	{
		if (CGame::isGameState(GameStates::Unpaused))
		{
			this->target.setMouseCursor(*cursors["csr_crosshair"]);
		}
		else if (CGame::isGameState(GameStates::Paused))
		{
			this->target.setMouseCursor(*cursors["csr_ship"]);
		}
	}
}