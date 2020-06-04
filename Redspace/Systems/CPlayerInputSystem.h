#ifndef CPLAYERINPUTSYSTEM_H
#define CPLAYERINPUTSYSTEM_H

class CPlayerInputSystem : public ex::System<CPlayerInputSystem>, public ex::Receiver<CPlayerInputSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	sf::Mouse::Button mouseButton;

public:
	/* ������� ����������� */
	explicit CPlayerInputSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CMouseInputEvent& mouseInputEvent);
};

#endif