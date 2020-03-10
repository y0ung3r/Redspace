#ifndef CRENDERSYSTEM_H
#define CRENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "../Components/CRenderComponent.h"

namespace ex = entityx;

/* �������, ����������� ������� ��������� �������� */
class CRenderSystem : public ex::System<CRenderSystem>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

public:
	/* ������� ����������� */
	explicit CRenderSystem(sf::RenderWindow& target) 
		: target(target) 
	{ }

	/* ��������� ������� ��������� �������� */
	void update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta) override;
};

#endif