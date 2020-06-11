#include <string>
#include <SFML/Graphics.hpp>

#include "../Enums/ObjectTypes.h"

#include "CTagComponent.h"

CTagComponent::CTagComponent(ObjectTypes tag)
	: tag(tag)
{ }

ObjectTypes CTagComponent::getTag()
{
	return this->tag;
}
