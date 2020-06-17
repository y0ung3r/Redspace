#ifndef CEFFECTFACTORY_H
#define CEFFECTFACTORY_H

#include "../Interfaces/IObjectFactory.h"

class CEffectFactory : public IObjectFactory
{
private:
	ex::EntityManager& entities;

	sf::RenderWindow& target;

public:
	CEffectFactory(ex::EntityManager& entities, sf::RenderWindow& target);

	virtual ex::Entity::Id create(std::string textureKey, sf::Vector2f position, float angleRotate) override;
};

#endif