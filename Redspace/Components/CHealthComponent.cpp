#include "CHealthComponent.h"

CHealthComponent::CHealthComponent(float maxHealth)
	: health(maxHealth), maxHealth(maxHealth)
{ }

float CHealthComponent::getHealth()
{
	return this->health;
}

void CHealthComponent::setHealth(float health)
{
	this->health = health;

	if (health <= 0.0f)
	{
		this->health = 0.0f;
	}
}

float CHealthComponent::getMaxHealth()
{
	return this->maxHealth;
}

bool CHealthComponent::isDead()
{
	return this->health == 0.0f;
}