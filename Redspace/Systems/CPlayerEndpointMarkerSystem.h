#ifndef CPLAYERENDPOINTMARKERSYSTEM_H
#define CPLAYERENDPOINTMARKERSYSTEM_H

class CPlayerEndpointMarkerSystem : public ex::System<CPlayerEndpointMarkerSystem>, public ex::Receiver<CPlayerEndpointMarkerSystem>
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

	sf::Mouse::Button mouseButton;

public:
	/* Базовый конструктор */
	explicit CPlayerEndpointMarkerSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	/* Обновляет систему управления курсором */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CMouseInputEvent& mouseInputEvent);
};

#endif