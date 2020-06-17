#ifndef CMAPFACTORY_H
#define CMAPFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CMapFactory : public IObjectFactory
{
private:
	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CMapFactory(ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif