#ifndef CPLAYERMOVEMENTSYSTEM_H
#define CPLAYERMOVEMENTSYSTEM_H

class CCollisionEvent;

/* �������, ����������� ������� ����������� ������ */
class CPlayerMovementSystem : public ex::System<CPlayerMovementSystem>, public ex::Receiver<CPlayerMovementSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* ������ �� ���� */
	sf::RenderWindow& target;
	
	/* ������������� ������ */
	ex::Entity::Id playerId;

public:
	/* ������� ����������� */
	explicit CPlayerMovementSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId);

	void configure(ex::EventManager& events) override;

	/* ��������� ������� ����������� ������ */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;

	void receive(const CCollisionEvent& collisionEvent);
};

#endif