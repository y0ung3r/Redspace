#include <vector>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"
#include "../Events/CMouseInputEvent.h"
#include "../Components/CInputComponent.h"
#include "../Components/CMovementComponent.h"
#include "../Components/CRenderingComponent.h"
#include "../Components/CEndpointMarkerComponent.h"
#include "../Components/CCircleBorderComponent.h"

#include "CPlayerEndpointMarkerSystem.h"

CPlayerEndpointMarkerSystem::CPlayerEndpointMarkerSystem(sf::RenderWindow& target)
	: target(target)
{ }

void CPlayerEndpointMarkerSystem::configure(ex::EventManager & events)
{
	events.subscribe<CMouseInputEvent>(*this);
}

void CPlayerEndpointMarkerSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	ex::ComponentHandle<CEndpointMarkerComponent> endpointMarkerComponent;
	ex::ComponentHandle<CInputComponent> inputComponent;
	ex::ComponentHandle<CMovementComponent> playerMovementComponent;

	for (ex::Entity entity : entities.entities_with_components(inputComponent, playerMovementComponent))
	{
		if (this->mouseButton == sf::Mouse::Right)
		{
			ex::Entity playerEndpointMarker = entities.create();

			CEndpointMarkerComponent playerEndpointMarkerComponent;
			playerEndpointMarkerComponent.lifeTime.restart();
			playerEndpointMarker.assign<CEndpointMarkerComponent>(playerEndpointMarkerComponent);

			CRenderingComponent playerEndpointMarkerRenderingComponent;

			std::map<std::string, sf::Texture*> markersTextures = CAssetsHelper::getInstance().getMarkersTextures();

			sf::Texture* playerEndpointMarkerTexture = markersTextures["marker_ep"];
			playerEndpointMarkerRenderingComponent.setTexture(*playerEndpointMarkerTexture);

			sf::Color color = sf::Color::Green;
			color.a = 0;
			playerEndpointMarkerRenderingComponent.setColor(color);

			sf::Vector2u playerEndpointMarkerSizeInPixels = playerEndpointMarkerTexture->getSize();
			sf::Vector2f playerEndpointMarkerSizeInCoords = static_cast<sf::Vector2f>(playerEndpointMarkerSizeInPixels);

			sf::Vector2f playerEndpointMarkerOrigin;
			playerEndpointMarkerOrigin.x = playerEndpointMarkerSizeInCoords.x / 2.0f;
			playerEndpointMarkerOrigin.y = playerEndpointMarkerSizeInCoords.y / 2.0f;
			playerEndpointMarkerRenderingComponent.setOrigin(playerEndpointMarkerOrigin);

			playerEndpointMarkerRenderingComponent.setPosition(playerMovementComponent->moveTo);

			playerEndpointMarker.assign<CRenderingComponent>(playerEndpointMarkerRenderingComponent);

			for (ex::Entity endpointMarker : entities.entities_with_components(endpointMarkerComponent))
			{
				if (playerEndpointMarker.id() != endpointMarker.id())
				{
					endpointMarker.destroy();
				}
			}
		}
	}

	this->mouseButton = sf::Mouse::Button::ButtonCount;

	ex::ComponentHandle<CRenderingComponent> endpointMarkerRenderingComponent;

	for (ex::Entity entity : entities.entities_with_components(endpointMarkerRenderingComponent, endpointMarkerComponent))
	{
		ex::ComponentHandle<CRenderingComponent> nearbyObjectRenderingComponent;
		ex::ComponentHandle<CCircleBorderComponent> nearbyObjectCircleBorderComponent;

		bool yetMustDraw = true;

		for (ex::Entity nearbyEntity : entities.entities_with_components(nearbyObjectRenderingComponent, nearbyObjectCircleBorderComponent))
		{
			sf::FloatRect nearbyObjectGlobalBounds = nearbyObjectCircleBorderComponent->circleShape.getGlobalBounds();

			if (nearbyObjectGlobalBounds.contains(playerMovementComponent->moveTo))
			{
				yetMustDraw = false;
			}
		}
		
		if (yetMustDraw)
		{
			endpointMarkerRenderingComponent->rotate(350.0f * timeDelta);

			sf::Color color = endpointMarkerRenderingComponent->getColor();

			int alpha = (color.a < 255) ? color.a + 15 : 255;

			float lifeTimeAsSeconds = endpointMarkerComponent->lifeTime.getElapsedTime().asSeconds();

			if (lifeTimeAsSeconds >= 0.25f)
			{
				alpha = (color.a > 0) ? color.a - 5 : 0;
			}

			sf::Color opacityMask = sf::Color(color.r, color.g, color.b, alpha);
			endpointMarkerRenderingComponent->setColor(opacityMask);

			if (lifeTimeAsSeconds >= 0.5f)
			{
				entity.destroy();
			}
		}
	}
}

void CPlayerEndpointMarkerSystem::receive(const CMouseInputEvent& mouseInputEvent)
{
	this->mouseButton = mouseInputEvent.instance.button;
}
