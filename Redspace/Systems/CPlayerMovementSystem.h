#ifndef CPLAYERMOVEMENTSYSTEM_H
#define CPLAYERMOVEMENTSYSTEM_H

class CPlayerMovementSystem;
class CVectorHelper;

/* �������, ����������� ������� ����������� ������ */
class CPlayerMovementSystem : public ex::System<CPlayerMovementSystem>
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

	/* ��������� ������� ����������� ������ */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif