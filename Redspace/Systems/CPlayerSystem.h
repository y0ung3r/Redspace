#ifndef CPLAYERSYSTEM_H
#define CPLAYERSYSTEM_H

class CPlayerSystem;
class CVectorHelper;

/* �������, ����������� ������� ����������� ������ */
class CPlayerSystem : public ex::System<CPlayerSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* ������ �� ���� */
	sf::RenderWindow& target;
	
	/* ������������� ������ */
	ex::Entity::Id playerId;

public:
	/* ������� ����������� */
	explicit CPlayerSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId);

	/* ��������� ������� ����������� ������ */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif