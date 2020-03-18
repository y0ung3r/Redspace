#include "CAssetsHelper.h"

CAssetsHelper& CAssetsHelper::getInstance()
{
	static CAssetsHelper assetsHelper;

	return assetsHelper;
}

void CAssetsHelper::configure()
{
	sf::Texture* mapBlackTexture = new sf::Texture();
	mapBlackTexture->loadFromFile("Resources/Textures/Background (black).png");
	mapBlackTexture->setRepeated(true);
	this->mapTextures.push_back(mapBlackTexture);

	sf::Texture* mapBlueTexture = new sf::Texture();
	mapBlueTexture->loadFromFile("Resources/Textures/Background (blue).png");
	mapBlueTexture->setRepeated(true);
	this->mapTextures.push_back(mapBlueTexture);

	sf::Texture* mapDarkTexture = new sf::Texture();
	mapDarkTexture->loadFromFile("Resources/Textures/Background (dark).png");
	mapDarkTexture->setRepeated(true);
	this->mapTextures.push_back(mapDarkTexture);

	sf::Texture* mapLightTexture = new sf::Texture();
	mapLightTexture->loadFromFile("Resources/Textures/Background (light).png");
	mapLightTexture->setRepeated(true);
	this->mapTextures.push_back(mapLightTexture);

	sf::Texture* crosshairTexture = new sf::Texture();
	crosshairTexture->loadFromFile("Resources/Sprites/Crosshair.png");
	this->crosshairTexture = crosshairTexture;

	sf::Texture* playerTexture = new sf::Texture();
	playerTexture->loadFromFile("Resources/Sprites/Player.png");
	this->playerTexture = playerTexture;

	sf::Texture* bigBrownMeteoriteTexture = new sf::Texture();
	bigBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, brown).png");
	this->meteoritesTextures.push_back(bigBrownMeteoriteTexture);

	sf::Texture* bigGrayMeteoriteTexture = new sf::Texture();
	bigGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, gray).png");
	this->meteoritesTextures.push_back(bigGrayMeteoriteTexture);

	sf::Texture* middleBrownMeteoriteTexture = new sf::Texture();
	middleBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, brown).png");
	this->meteoritesTextures.push_back(middleBrownMeteoriteTexture);

	sf::Texture* middleGrayMeteoriteTexture = new sf::Texture();
	middleGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, gray).png");
	this->meteoritesTextures.push_back(middleGrayMeteoriteTexture);

	sf::Texture* smallBrownMeteoriteTexture = new sf::Texture();
	smallBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, brown).png");
	this->meteoritesTextures.push_back(smallBrownMeteoriteTexture);

	sf::Texture* smallGrayMeteoriteTexture = new sf::Texture();
	smallGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, gray).png");
	this->meteoritesTextures.push_back(smallGrayMeteoriteTexture);
}

const std::vector<sf::Texture*> CAssetsHelper::getMapTextures()
{
	return this->mapTextures;
}

sf::Texture* CAssetsHelper::getCrosshairTexture()
{
	return this->crosshairTexture;
}

sf::Texture* CAssetsHelper::getPlayerTexture()
{
	return this->playerTexture;
}

const std::vector<sf::Texture*> CAssetsHelper::getMeteoritesTextures()
{
	return this->meteoritesTextures;
}

