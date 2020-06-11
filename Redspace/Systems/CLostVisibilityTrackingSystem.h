#ifndef CLOSTVISIBILITYTRACKINGSYSTEM_H
#define CLOSTVISIBILITYTRACKINGSYSTEM_H

class CLostVisibilityTrackingSystem : public ex::System<CLostVisibilityTrackingSystem>
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Идентификатор карты */
	ex::Entity::Id mapId;

public:
	/* Базовый конструктор */
	explicit CLostVisibilityTrackingSystem(sf::RenderWindow& target, ex::Entity::Id mapId);

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif