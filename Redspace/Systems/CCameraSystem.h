#ifndef CCAMERASYSTEM_H
#define CCAMERASYSTEM_H

class CCameraSystem;

/* �������, ����������� ������� ��������� ������ */
class CCameraSystem : public ex::System<CCameraSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������������� ������ */
	ex::Entity::Id cameraId;

	/* ������������� ����� */
	ex::Entity::Id mapId;

	/* ������������� �������, � �������� ��������� ������ */
	ex::Entity::Id objectId;

public:
	/* ������� ����������� */
	explicit CCameraSystem(sf::RenderWindow& target, ex::Entity::Id cameraId, ex::Entity::Id mapId, ex::Entity::Id objectId);

	/* ��������� ������� ���������� ������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif