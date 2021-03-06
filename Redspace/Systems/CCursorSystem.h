#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

class CGameStateChangedEvent;
class CMouseHoverEvent;
class CMouseExitEvent;

/* �������, ����������� ������� ��������� ������� */
class CCursorSystem : public ex::System<CCursorSystem>, public ex::Receiver<CCursorSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	std::map<std::string, sf::Cursor*> cursors;

	sf::Cursor* cursor;

	bool isCursorHover;

	ex::Entity hoveredObject;

	GameStates gameState;

public:
	/* ������� ����������� */
	explicit CCursorSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CGameStateChangedEvent& gameStateChangedEvent);

	void receive(const CMouseHoverEvent& mouseHoverEvent);

	void receive(const CMouseExitEvent& mouseExitEvent);
};

#endif

