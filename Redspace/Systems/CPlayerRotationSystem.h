#ifndef CPLAYERROTATIONSYSTEM_H
#define CPLAYERROTATIONSYSTEM_H

class CPlayerRotationSystem : public ex::System<CPlayerRotationSystem>
{
private:
	CVectorHelper& vectorHelper;

	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������������� ������ */
	ex::Entity::Id playerId;

public:
	/* ������� ����������� */
	explicit CPlayerRotationSystem(CVectorHelper& vectorHelper, sf::RenderWindow& target, ex::Entity::Id& playerId);

	/* ��������� ������� ����������� ������ */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif