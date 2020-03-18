#include "CMeteoriteSystem.h"

void CMeteoriteSystem::update(ex::EntityManager& entities, ex::EventManager& events, ex::TimeDelta timeDelta)
{
	int counter = 0;

	std::default_random_engine randomGenerator(static_cast<unsigned int>(std::time(0)));
	std::vector<sf::Texture*> meteoritesTextures = CAssetsHelper::getInstance().getMeteoritesTextures();

	ex::Entity map = entities.get(this->mapId);
	ex::ComponentHandle<CRenderComponent> mapRenderComponent = map.component<CRenderComponent>();

	sf::FloatRect mapGlobalBounds = mapRenderComponent->getGlobalBounds();

	ex::ComponentHandle<CRenderComponent> renderComponent;
	ex::ComponentHandle<CMovementComponent> movementComponent;
	ex::ComponentHandle<CMeteoriteComponent> meteoriteComponent;

	for (ex::Entity entity : entities.entities_with_components(renderComponent, movementComponent, meteoriteComponent))
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

		CMeteoriteComponent meteoriteComponent;
		CRenderComponent meteoriteRenderComponent;

		std::uniform_int_distribution<int> textureNumberDistribution(0, static_cast<int>(meteoritesTextures.size()) - 1);
		int textureNumber = textureNumberDistribution(randomGenerator);

		sf::Texture* meteoriteTexture = meteoritesTextures[textureNumber];
		meteoriteRenderComponent.setTexture(*meteoriteTexture);

		sf::Vector2u meteoriteTextureSizeInPixels = meteoriteTexture->getSize();
		sf::Vector2f meteoriteTextureSizeInCoords = static_cast<sf::Vector2f>(meteoriteTextureSizeInPixels);

		sf::Vector2f meteoriteOrigin;
		meteoriteOrigin.x = meteoriteTextureSizeInCoords.x / 2.0f;
		meteoriteOrigin.y = meteoriteTextureSizeInCoords.y / 2.0f;
		meteoriteRenderComponent.setOrigin(meteoriteOrigin);

		sf::IntRect mapSize = mapRenderComponent->getTextureRect();

		std::uniform_real_distribution<float> positionDistributionX(static_cast<float>(mapSize.left), static_cast<float>(mapSize.width));
		float positionX = positionDistributionX(randomGenerator);

		std::uniform_real_distribution<float> positionDistributionY(static_cast<float>(mapSize.top), static_cast<float>(mapSize.height));
		float positionY = positionDistributionY(randomGenerator);

		sf::Vector2f meteoritePosition = sf::Vector2f(positionX, positionY);
		meteoriteRenderComponent.setPosition(meteoritePosition);

		meteorite.assign<CRenderComponent>(meteoriteRenderComponent);
		meteorite.assign<CMeteoriteComponent>(meteoriteComponent);

		CMovementComponent meteoriteMovementComponent(25.0f);

		std::uniform_real_distribution<float> directionDistributionX(-1.0f, 1.0f);
		float directionX = directionDistributionX(randomGenerator);

		std::uniform_real_distribution<float> directionDistributionY(-1.0f, 1.0f);
		float directionY = directionDistributionY(randomGenerator);

		meteoriteMovementComponent.setDirection(directionX, directionY);

		meteorite.assign<CMovementComponent>(meteoriteMovementComponent);
	}
}
