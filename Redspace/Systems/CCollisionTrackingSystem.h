#ifndef CCOLLISIONTRACKINGSYSTEM_H
#define CCOLLISIONTRACKINGSYSTEM_H

class CCollisionTrackingSystem;

/* �������, ����������� ������� ������������ �������� */
class CCollisionTrackingSystem : public ex::System<CCollisionTrackingSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CCollisionTrackingSystem(sf::RenderWindow& target);

	/* ��������� ������� ������������ �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif