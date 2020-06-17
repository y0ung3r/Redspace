#ifndef CWEAPONCOMPONENT_H
#define CWEAPONCOMPONENT_H

class CWeaponComponent
{
private:
	float cooldown;

	float maxCooldown;

public:
	CWeaponComponent(float maxCooldown);

	bool canShot();

	void resetCooldown();
};

#endif