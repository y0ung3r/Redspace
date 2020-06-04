#ifndef CCIRCLEBORDERRENDERINGSYSTEM_H
#define CCIRCLEBORDERRENDERINGSYSTEM_H

class CCircleBorderRenderingSystem : public ex::System<CCircleBorderRenderingSystem>
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

public:
	/* Базовый конструктор */
	explicit CCircleBorderRenderingSystem(sf::RenderWindow& target);

	/* Обновляет систему управления курсором */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif