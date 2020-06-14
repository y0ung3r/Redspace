#ifndef CHEALTHCOMPONENT_H
#define CHEALTHCOMPONENT_H

class CHealthComponent
{
private:
	float health;

	float maxHealth;

public:
	CHealthComponent(float maxHealth);

	float getHealth();

	void setHealth(float health);
	
	bool isDead();
};

#endif