#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CSingleMouseInputEvent.h"
#include "../Interfaces/IObjectFactory.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CBulletMovementComponent.h"
#include "../Components/CWeaponComponent.h"

#include "CShootingSystem.h"

CShootingSystem::CShootingSystem(IObjectFactory& bulletFactory, sf::RenderWindow& target)
	: bulletFactory(bulletFactory), target(target)
{ }

void CShootingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CMovementComponent*> entityBaseMovementComponent;
	ex::ComponentHandle<CWeaponComponent> entityWeaponComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityBaseMovementComponent, entityWeaponComponent))
	{
		CMovementComponent* entityMovementComponent = *entityBaseMovementComponent.get();

		bool canAttack = false;
		bool canShot = entityWeaponComponent->canShot();

		sf::Vector2f entityPosition = entityRenderingComponent->getPosition();
		float entityAngleRotate = entityRenderingComponent->getRotation();

		ObjectTypes entityTag = entityTagComponent->getTag();

		switch (entityTag)
		{

		case Player:
		{
			canAttack = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		}
		break;

		case Enemy:
		{
			
		}
		break;

		}

		if (canAttack && canShot)
		{
			bulletFactory.create("bullet_blue", entityPosition, entityAngleRotate);
		}
	}
}