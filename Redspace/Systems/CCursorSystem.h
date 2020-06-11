#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

class CGameStateChangedEvent;
class CMouseHoverEvent;

/* �������, ����������� ������� ��������� ������� */
class CCursorSystem : public ex::System<CCursorSystem>, public ex::Receiver<CCursorSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	std::map<std::string, sf::Cursor*> cursors;

	sf::Cursor* cursor;

public:
	/* ������� ����������� */
	explicit CCursorSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CGameStateChangedEvent& gameStateChangedEvent);

	void receive(const CMouseHoverEvent& mouseHoverEvent);
};

#endif

