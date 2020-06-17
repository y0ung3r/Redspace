#include "CViewRadiusComponent.h"

CViewRadiusComponent::CViewRadiusComponent(float viewRadius)
	: viewRadius(viewRadius)
{ }

float CViewRadiusComponent::getViewRadius()
{
	return this->viewRadius;
}
