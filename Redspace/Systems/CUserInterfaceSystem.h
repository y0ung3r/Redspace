#ifndef CUSERINTERFACESYSTEM_H
#define CUSERINTERFACESYSTEM_H

#include "../Core/CGame.h"
class CMouseHoverEvent;
class CMouseExitEvent;

class CUserInterfaceSystem : public ex::System<CUserInterfaceSystem>, public ex::Receiver<CUserInterfaceSystem>
{
private:
	CGame& game;

	sf::RenderWindow& target;

	bool canDrawInfoAboutThings;

	ex::Entity hoveredObject;

public:
	explicit CUserInterfaceSystem(CGame& game, sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CMouseHoverEvent& mouseHoverEvent);

	void receive(const CMouseExitEvent& mouseExitEvent);
};

#endif