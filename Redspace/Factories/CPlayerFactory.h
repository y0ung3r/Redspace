#ifndef CPLAYERFACTORY_H
#define CPLAYERFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CPlayerFactory : public IObjectFactory
{
private:
	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CPlayerFactory(ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif