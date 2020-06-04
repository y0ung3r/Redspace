#ifndef CRENDERINGSYSTEM_H
#define CRENDERINGSYSTEM_H

/* —истема, управл€юща€ логикой отрисовки объектов */
class CRenderingSystem : public ex::System<CRenderingSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CRenderingSystem(sf::RenderWindow& target);

	/* ќбновл€ет систему отрисовки объектов */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif