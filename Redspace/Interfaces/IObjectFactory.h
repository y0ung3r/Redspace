#ifndef IOBJECTFACTORY_H
#define IOBJECTFACTORY_H

class IObjectFactory
{
public:
	virtual ex::Entity::Id create(std::string textureKey = "", sf::Vector2f position = sf::Vector2f(), float angleRotate = 0.0f) = 0;
};

#endif