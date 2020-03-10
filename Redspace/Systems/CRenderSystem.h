#ifndef CRENDERSYSTEM_H
#define CRENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* —истема, управл€юща€ логикой отрисовки объектов */
class CRenderSystem : public ex::System<CRenderSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CRenderSystem(sf::RenderWindow& target) 
		: target(target) 
	{ }

	/* ќбновл€ет систему отрисовки объектов */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif