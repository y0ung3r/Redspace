#ifndef CCAMERAFACTORY_H
#define CCAMERAFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CCameraFactory : public IObjectFactory
{
private:
	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CCameraFactory(ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif