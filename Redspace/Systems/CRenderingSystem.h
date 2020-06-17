#ifndef CRENDERINGSYSTEM_H
#define CRENDERINGSYSTEM_H

/* �������, ����������� ������� ��������� �������� */
class CRenderingSystem : public ex::System<CRenderingSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CRenderingSystem(sf::RenderWindow& target);

	/* ��������� ������� ��������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif