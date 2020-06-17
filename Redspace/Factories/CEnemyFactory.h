#ifndef CENEMYFACTORY_H
#define CENEMYFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CEnemyFactory : public IObjectFactory
{
private:
	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CEnemyFactory(ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif