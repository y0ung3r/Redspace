#ifndef CRENDERSYSTEM_H
#define CRENDERSYSTEM_H

/* —истема, управл€юща€ логикой отрисовки объектов */
class CRenderSystem : public ex::System<CRenderSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CRenderSystem(sf::RenderWindow& target);

	/* ќбновл€ет систему отрисовки объектов */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif