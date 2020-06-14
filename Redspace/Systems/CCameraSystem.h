#ifndef CCAMERASYSTEM_H
#define CCAMERASYSTEM_H

#include "../Core/CGame.h"

/* Система, управляющая логикой поведения камеры */
class CCameraSystem : public ex::System<CCameraSystem>
{
private:
	CGame& game;

	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Идентификатор камеры */
	ex::Entity::Id cameraId;

	/* Идентификатор карты */
	ex::Entity::Id mapId;

	/* Идентификатор объекта, к которому привязана камера */
	ex::Entity::Id objectId;

public:
	/* Базовый конструктор */
	explicit CCameraSystem(CGame& game, sf::RenderWindow& target);

	/* Обновляет систему управления камерой */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif