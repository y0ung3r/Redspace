#ifndef CGAME_H
#define CGAME_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"
#include "../Components/CCameraComponent.h"
#include "../Systems/CRenderSystem.h"
#include "../Systems/CCursorSystem.h"
#include "../Systems/CCameraSystem.h"
#include "../Systems/CPlayerSystem.h"
#include "../Systems/CMeteoriteSystem.h"

namespace ex = entityx;

/* Основной класс игры */
class CGame : public ex::EntityX
{
private:
	sf::RenderWindow& target;

	/* Создает карту и возвращает ее идентификатор */
	ex::Entity::Id createMap();

	/* Создает курсор и возвращает его идентификатор */
	ex::Entity::Id createCursor();

	/* Создает объект камеры и возвращает его идентификатор */
	ex::Entity::Id createCamera();

	/* Создает игрока и возвращает его идентификатор */
	ex::Entity::Id createPlayer();

public:
	/* Базовый конструктор */
	explicit CGame(sf::RenderWindow& target);

	/* Обновляет игру */
	void update(ex::TimeDelta timeDelta);
};

#endif