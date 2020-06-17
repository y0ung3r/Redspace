#ifndef CBULLETFACTORY_H
#define CBULLETFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CBulletFactory : public IObjectFactory
{
private:
	CVectorHelper& vectorHelper;

	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CBulletFactory(CVectorHelper& vectorHelper, ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif