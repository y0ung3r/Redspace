#ifndef CCOLLISIONSYSTEM_H
#define CCOLLISIONSYSTEM_H

class CCollisionSystem;

/* �������, ����������� ������� ������������ �������� */
class CCollisionSystem : public ex::System<CCollisionSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CCollisionSystem(sf::RenderWindow& target);

	/* ��������� ������� ������������ �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif