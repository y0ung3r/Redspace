#include <SFML/Graphics.hpp>

#include "CWeaponComponent.h"

CWeaponComponent::CWeaponComponent(float maxCooldown)
	: cooldown(0.0f), maxCooldown(maxCooldown)
{ }

bool CWeaponComponent::canShot()
{
	bool canShot = false;

	if (this->cooldown >= this->maxCooldown)
	{
		this->cooldown = 0.0f;

		canShot = true;
	}
	else
	{
		this->cooldown += 1.0f;
	}
		
	return canShot;
}

void CWeaponComponent::resetCooldown()
{
	this->cooldown = this->maxCooldown;
}
