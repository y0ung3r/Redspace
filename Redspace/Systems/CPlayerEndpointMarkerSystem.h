#ifndef CPLAYERENDPOINTMARKERSYSTEM_H
#define CPLAYERENDPOINTMARKERSYSTEM_H

class CPlayerEndpointMarkerSystem : public ex::System<CPlayerEndpointMarkerSystem>, public ex::Receiver<CPlayerEndpointMarkerSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	sf::Mouse::Button mouseButton;

public:
	/* ������� ����������� */
	explicit CPlayerEndpointMarkerSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CMouseInputEvent& mouseInputEvent);
};

#endif