#ifndef CRENDERSYSTEM_H
#define CRENDERSYSTEM_H

/* �������, ����������� ������� ��������� �������� */
class CRenderSystem : public ex::System<CRenderSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CRenderSystem(sf::RenderWindow& target);

	/* ��������� ������� ��������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif