#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Helpers/CAssetsHelper.h"
#include "../Core/CGame.h"
#include "../Enums/GameStates.h"
#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* —истема, управл€юща€ логикой поведени€ курсора */
class CCursorSystem : public ex::System<CCursorSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CCursorSystem(sf::RenderWindow& target)
		: target(target)
	{ }

	/* ќбновл€ет систему управлени€ курсором */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif

