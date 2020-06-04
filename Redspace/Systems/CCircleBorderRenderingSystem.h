#ifndef CCIRCLEBORDERRENDERINGSYSTEM_H
#define CCIRCLEBORDERRENDERINGSYSTEM_H

class CCircleBorderRenderingSystem : public ex::System<CCircleBorderRenderingSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CCircleBorderRenderingSystem(sf::RenderWindow& target);

	/* ��������� ������� ���������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif