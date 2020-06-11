#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Core/CGame.h"
#include "../Helpers/CAssetsHelper.h"
#include "../Helpers/CVectorHelper.h"
#include "../Enums/ObjectTypes.h"
#include "../Events/CSingleMouseInputEvent.h"
#include "../Events/CShotFiredEvent.h"
#include "../Interfaces/IObjectFactory.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CTagComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CDirectionMovementComponent.h"
#include "../Components/CWeaponComponent.h"

#include "CShootingSystem.h"

CShootingSystem::CShootingSystem(IObjectFactory& bulletFactory, sf::RenderWindow& target)
	: bulletFactory(bulletFactory), target(target)
{ }

void CShootingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CWeaponComponent> entityWeaponComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityWeaponComponent))
	{
		bool canAttack = false;
		bool canShot = entityWeaponComponent->canShot();

		std::string textureKey;
		sf::Vector2f entityPosition = entityRenderingComponent->getPosition();
		float entityAngleRotate = entityRenderingComponent->getRotation();

		ObjectTypes entityTag = entityTagComponent->getTag();

		switch (entityTag)
		{

		case Player:
		{
			textureKey = "bullet_blue";

			canAttack = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		}
		break;

		case Enemy:
		{
			textureKey = "bullet_red";


		}
		break;

		}

		if (canAttack && canShot)
		{
			bulletFactory.create(textureKey, entityPosition, entityAngleRotate);

			events.emit<CShotFiredEvent>(entity);
		}
	}
}