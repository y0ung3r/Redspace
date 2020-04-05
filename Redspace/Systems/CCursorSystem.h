#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

class CCursorSystem;

/* —истема, управл€юща€ логикой поведени€ курсора */
class CCursorSystem : public ex::System<CCursorSystem>
{
private:
	/* —сылка на окно */
	sf::RenderWindow& target;

public:
	/* Ѕазовый конструктор */
	explicit CCursorSystem(sf::RenderWindow& target);

	/* ќбновл€ет систему управлени€ курсором */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif

