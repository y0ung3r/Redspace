#include "CMeteoriteSystem.h"

void CMeteoriteSystem::configure(ex::EventManager& events)
{
	events.subscribe<CCollisionEvent>(*this);
}

void CMeteoriteSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	int counter = 0;

	time_t time = std::time(0);
	unsigned int seed = static_cast<unsigned int>(time);
	std::default_random_engine randomGenerator(seed);

	ex::Entity map = entities.get(this->mapId);
	ex::ComponentHandle<CRenderComponent> mapRenderComponent = map.component<CRenderComponent>();

	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();

	std::vector<sf::Texture*> meteoritesTextures = CAssetsHelper::getInstance().getMeteoritesTextures();
	size_t meteoritesTexturesSize = meteoritesTextures.size();
	int meteoritesTexturesCount = static_cast<int>(meteoritesTexturesSize);

	ex::ComponentHandle<CRenderComponent> renderComponent;
	ex::ComponentHandle<CMovementComponent> movementComponent;
	ex::ComponentHandle<CCollisionComponent> collisionComponent;
	ex::ComponentHandle<CMeteoriteComponent> component;

	for (ex::Entity entity : entities.entities_with_components(renderComponent, movementComponent, collisionComponent, component))
	{
		counter++;

		sf::FloatRect globalBounds = renderComponent->getGlobalBounds();

		sf::Vector2f direction = movementComponent->getSpeed(timeDelta);
		renderComponent->move(direction);

		renderComponent->rotate(0.2f);

		if (!globalBounds.intersects(mapGlobalBounds))
		{
			entity.destroy();

			this->count--;
		}
	}

	for (int i = 0; i < count - counter; i++)
	{
		ex::Entity meteorite = entities.create();

		CRenderComponent meteoriteRenderComponent;

		std::uniform_int_distribution<int> textureNumberDistribution(0, meteoritesTexturesCount - 1);
		int textureNumber = textureNumberDistribution(randomGenerator);

		sf::Texture* meteoriteTexture = meteoritesTextures[textureNumber];
		meteoriteRenderComponent.setTexture(*meteoriteTexture);

		sf::Vector2u meteoriteTextureSizeInPixels = meteoriteTexture->getSize();
		sf::Vector2f meteoriteTextureSizeInCoords = static_cast<sf::Vector2f>(meteoriteTextureSizeInPixels);

		sf::Vector2f meteoriteOrigin;
		meteoriteOrigin.x = meteoriteTextureSizeInCoords.x / 2.0f;
		meteoriteOrigin.y = meteoriteTextureSizeInCoords.y / 2.0f;
		meteoriteRenderComponent.setOrigin(meteoriteOrigin);

		sf::FloatRect mapSize = mapRenderComponent->getGlobalBounds();

		std::uniform_real_distribution<float> positionDistributionX(mapSize.left, mapSize.width);
		float positionX = positionDistributionX(randomGenerator);

		std::uniform_real_distribution<float> positionDistributionY(mapSize.top, mapSize.height);
		float positionY = positionDistributionY(randomGenerator);

		sf::Vector2f meteoritePosition = sf::Vector2f(positionX, positionY);
		meteoriteRenderComponent.setPosition(meteoritePosition);

		meteorite.assign<CRenderComponent>(meteoriteRenderComponent);

		CMovementComponent meteoriteMovementComponent(25.0f);

		std::uniform_real_distribution<float> directionDistributionX(-1.0f, 1.0f);
		float directionX = directionDistributionX(randomGenerator);

		std::uniform_real_distribution<float> directionDistributionY(-1.0f, 1.0f);
		float directionY = directionDistributionY(randomGenerator);

		meteoriteMovementComponent.setDirection(directionX, directionY);

		meteorite.assign<CMovementComponent>(meteoriteMovementComponent);

		CCollisionComponent meteoriteCollisionComponent;
		meteorite.assign<CCollisionComponent>(meteoriteCollisionComponent);

		CMeteoriteComponent meteoriteComponent;
		meteorite.assign<CMeteoriteComponent>();
	}
}

void CMeteoriteSystem::receive(const CCollisionEvent& collisionEvent)
{
	ex::Entity firstMeteorite = collisionEvent.getFirstEntity();
	ex::Entity secondMeteorite = collisionEvent.getSecondEntity();

	if (!firstMeteorite.has_component<CMeteoriteComponent>() || !secondMeteorite.has_component<CMeteoriteComponent>())
	{
		return;
	}

	if (firstMeteorite.valid() && secondMeteorite.valid())
	{
		ex::ComponentHandle<CRenderComponent> firstMeteoriteRenderComponent = firstMeteorite.component<CRenderComponent>();
		ex::ComponentHandle<CMovementComponent> firstMeteoriteMovementComponent = firstMeteorite.component<CMovementComponent>();

		ex::ComponentHandle<CRenderComponent> secondMeteoriteRenderComponent = secondMeteorite.component<CRenderComponent>();
		ex::ComponentHandle<CMovementComponent> secondMeteoriteMovementComponent = secondMeteorite.component<CMovementComponent>();
	}
}