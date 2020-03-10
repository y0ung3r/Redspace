#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

#include <SFML/Graphics.hpp>
#include "entityx/entityx.h"

#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* —истема, управл€юща€ логикой поведени€ курсора */
class CCursorSystem : public ex::System<CCursorSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

	/* »дентификатор курсора */
	ex::Entity::Id cursorId;

public:
	/* Ѕазовый конструктор */
	explicit CCursorSystem(sf::RenderWindow& target, ex::Entity::Id& cursorId)
		: target(target), cursorId(cursorId)
	{ }

	/* ќбновл€ет систему управлени€ курсором */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif

