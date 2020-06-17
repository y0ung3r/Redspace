#ifndef CMETEORITEFACTORY_H
#define CMETEORITEFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CMeteoriteFactory : public IObjectFactory
{
private:
	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CMeteoriteFactory(ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif