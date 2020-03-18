#include "CAssetsHelper.h"

CAssetsHelper& CAssetsHelper::getInstance()
{
	static CAssetsHelper assetsHelper;

	return assetsHelper;
}

void CAssetsHelper::configure(bool isTexturesSmooth)
{
	sf::Texture* mapBlackTexture = new sf::Texture();
	mapBlackTexture->loadFromFile("Resources/Textures/Background (black).png");
	mapBlackTexture->setRepeated(true);
	mapBlackTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.push_back(mapBlackTexture);

	sf::Texture* mapBlueTexture = new sf::Texture();
	mapBlueTexture->loadFromFile("Resources/Textures/Background (blue).png");
	mapBlueTexture->setRepeated(true);
	mapBlueTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.push_back(mapBlueTexture);

	sf::Texture* mapDarkTexture = new sf::Texture();
	mapDarkTexture->loadFromFile("Resources/Textures/Background (dark).png");
	mapDarkTexture->setRepeated(true);
	mapDarkTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.push_back(mapDarkTexture);

	sf::Texture* mapLightTexture = new sf::Texture();
	mapLightTexture->loadFromFile("Resources/Textures/Background (light).png");
	mapLightTexture->setRepeated(true);
	mapLightTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.push_back(mapLightTexture);

	sf::Texture* cursorShipTexture = new sf::Texture();
	cursorShipTexture->loadFromFile("Resources/Sprites/Cursor (ship).png");
	cursorShipTexture->setSmooth(isTexturesSmooth);
	sf::Image cursorShipImage = cursorShipTexture->copyToImage();
	const sf::Uint8* cursorShipPixels = cursorShipImage.getPixelsPtr();
	sf::Cursor* cursorShip = new sf::Cursor();
	sf::Vector2u cursorShipSize = cursorShipTexture->getSize();
	sf::Vector2u cursorShipHotspot = sf::Vector2u();
	cursorShipHotspot.x = cursorShipSize.x / 2;
	cursorShipHotspot.y = cursorShipSize.y / 2;
	cursorShip->loadFromPixels(cursorShipPixels, cursorShipSize, cursorShipHotspot);
	this->cursors.push_back(cursorShip);

	sf::Texture* cursorCrosshairTexture = new sf::Texture();
	cursorCrosshairTexture->loadFromFile("Resources/Sprites/Cursor (crosshair).png");
	cursorCrosshairTexture->setSmooth(isTexturesSmooth);
	sf::Image cursorCrosshairImage = cursorCrosshairTexture->copyToImage();
	const sf::Uint8* cursorCrosshairPixels = cursorCrosshairImage.getPixelsPtr();
	sf::Cursor* cursorCrosshair = new sf::Cursor();
	sf::Vector2u cursorCrosshairSize = cursorCrosshairTexture->getSize();
	sf::Vector2u cursorCrosshairHotspot = sf::Vector2u();
	cursorCrosshairHotspot.x = cursorCrosshairSize.x / 2;
	cursorCrosshairHotspot.y = cursorCrosshairSize.y / 2;
	cursorCrosshair->loadFromPixels(cursorCrosshairPixels, cursorCrosshairSize, cursorCrosshairHotspot);
	this->cursors.push_back(cursorCrosshair);

	sf::Texture* playerTexture = new sf::Texture();
	playerTexture->loadFromFile("Resources/Sprites/Player.png");
	playerTexture->setSmooth(isTexturesSmooth);
	this->playerTexture = playerTexture;

	sf::Texture* bigBrownMeteoriteTexture = new sf::Texture();
	bigBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, brown).png");
	bigBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.push_back(bigBrownMeteoriteTexture);

	sf::Texture* bigGrayMeteoriteTexture = new sf::Texture();
	bigGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, gray).png");
	bigGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.push_back(bigGrayMeteoriteTexture);

	sf::Texture* middleBrownMeteoriteTexture = new sf::Texture();
	middleBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, brown).png");
	middleBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.push_back(middleBrownMeteoriteTexture);

	sf::Texture* middleGrayMeteoriteTexture = new sf::Texture();
	middleGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, gray).png");
	middleGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.push_back(middleGrayMeteoriteTexture);

	sf::Texture* smallBrownMeteoriteTexture = new sf::Texture();
	smallBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, brown).png");
	smallBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.push_back(smallBrownMeteoriteTexture);

	sf::Texture* smallGrayMeteoriteTexture = new sf::Texture();
	smallGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, gray).png");
	smallGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.push_back(smallGrayMeteoriteTexture);
}

const std::vector<sf::Texture*> CAssetsHelper::getMapTextures()
{
	return this->mapTextures;
}

const std::vector<sf::Cursor*> CAssetsHelper::getCursors()
{
	return this->cursors;
}

sf::Texture* CAssetsHelper::getPlayerTexture()
{
	return this->playerTexture;
}

const std::vector<sf::Texture*> CAssetsHelper::getMeteoritesTextures()
{
	return this->meteoritesTextures;
}

