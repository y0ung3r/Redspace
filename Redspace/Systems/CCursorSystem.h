#ifndef CCURSORSYSTEM_H
#define CCURSORSYSTEM_H

class CCursorSystem;

/* �������, ����������� ������� ��������� ������� */
class CCursorSystem : public ex::System<CCursorSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CCursorSystem(sf::RenderWindow& target);

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif

