#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Extensions/Collision.h"
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
#include "../Components/CViewRadiusComponent.h"

#include "CShootingSystem.h"

CShootingSystem::CShootingSystem(CGame& game, CVectorHelper& vectorHelper, IObjectFactory& bulletFactory, sf::RenderWindow& target)
	: game(game), vectorHelper(vectorHelper), bulletFactory(bulletFactory), target(target)
{ }

void CShootingSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::Entity::Id playerId = this->game.getPlayerId();
	ex::Entity player = entities.get(playerId);
	ex::ComponentHandle<CRenderingComponent> playerRenderingComponent = player.component<CRenderingComponent>();
	CRenderingComponent playerSprite = *playerRenderingComponent.get();

	ex::ComponentHandle<CRenderingComponent> entityRenderingComponent;
	ex::ComponentHandle<CTagComponent> entityTagComponent;
	ex::ComponentHandle<CWeaponComponent> entityWeaponComponent;

	for (ex::Entity entity : entities.entities_with_components(entityRenderingComponent, entityTagComponent, entityWeaponComponent))
	{
		bool canAttack = false;
		bool canShot = entityWeaponComponent->canShot();

		std::string textureKey;
		sf::Vector2f entityOrigin = entityRenderingComponent->getOrigin();
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

			ex::ComponentHandle<CViewRadiusComponent> viewRadiusComponent = entity.component<CViewRadiusComponent>();

			float viewRadius = viewRadiusComponent->getViewRadius();

			sf::CircleShape viewRadiusCircle;

			sf::Vector2f viewRadiusCircleOrigin = sf::Vector2f(viewRadius, viewRadius);
			viewRadiusCircle.setOrigin(viewRadiusCircleOrigin);

			viewRadiusCircle.setRadius(viewRadius);
			viewRadiusCircle.setPosition(entityPosition);
			viewRadiusCircle.setRotation(entityAngleRotate);

			if (Collision::CircleTest(playerSprite, viewRadiusCircle))
			{
				sf::Vector2f playerPosition = playerRenderingComponent->getPosition();
				entityAngleRotate = vectorHelper.getAngleInDegrees(playerPosition, entityPosition);

				entityRenderingComponent->setRotation(entityAngleRotate);

				canAttack = true;
			}
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