#include "CCursorSystem.h"

void CCursorSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity cursor = entities.get(this->cursorId);

	ex::ComponentHandle<CRenderComponent> cursorRenderComponent = cursor.component<CRenderComponent>();

	sf::Vector2i mousePositionInPixels = sf::Mouse::getPosition(this->target);
	sf::Vector2f mousePositionInCoords = this->target.mapPixelToCoords(mousePositionInPixels);

	cursorRenderComponent->rotate(0.5f);

	cursorRenderComponent->setPosition(mousePositionInCoords);
}