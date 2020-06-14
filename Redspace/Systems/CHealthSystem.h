#ifndef CHEALTHSYSTEM_H
#define CHEALTHSYSTEM_H

class CCollisionEvent;

class CHealthSystem : public ex::System<CHealthSystem>, public ex::Receiver<CHealthSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	std::vector<ex::Entity> listOfDestruction;

public:
	/* ������� ����������� */
	explicit CHealthSystem(sf::RenderWindow& target);

	void configure(ex::EventManager& events) override;

	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CCollisionEvent& collisionEvent);
};

#endif