#include <map>
#include <SFML/Graphics.hpp>

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
	this->mapTextures.insert(std::pair<std::string, sf::Texture*>("bg_black", mapBlackTexture));

	sf::Texture* mapBlueTexture = new sf::Texture();
	mapBlueTexture->loadFromFile("Resources/Textures/Background (blue).png");
	mapBlueTexture->setRepeated(true);
	mapBlueTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.insert(std::pair<std::string, sf::Texture*>("bg_blue", mapBlueTexture));

	sf::Texture* mapDarkTexture = new sf::Texture();
	mapDarkTexture->loadFromFile("Resources/Textures/Background (dark).png");
	mapDarkTexture->setRepeated(true);
	mapDarkTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.insert(std::pair<std::string, sf::Texture*>("bg_dark", mapDarkTexture));

	sf::Texture* mapLightTexture = new sf::Texture();
	mapLightTexture->loadFromFile("Resources/Textures/Background (light).png");
	mapLightTexture->setRepeated(true);
	mapLightTexture->setSmooth(isTexturesSmooth);
	this->mapTextures.insert(std::pair<std::string, sf::Texture*>("bg_light", mapLightTexture));

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
	this->cursors.insert(std::pair<std::string, sf::Cursor*>("csr_ship", cursorShip));

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
	this->cursors.insert(std::pair<std::string, sf::Cursor*>("csr_crosshair", cursorCrosshair));

	sf::Texture* playerTexture = new sf::Texture();
	playerTexture->loadFromFile("Resources/Sprites/Player.png");
	playerTexture->setSmooth(isTexturesSmooth);
	this->playerTexture = playerTexture;

	sf::Texture* bigBrownMeteoriteTexture = new sf::Texture();
	bigBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, brown).png");
	bigBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_big_brown", bigBrownMeteoriteTexture));

	sf::Texture* bigGrayMeteoriteTexture = new sf::Texture();
	bigGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, gray).png");
	bigGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_big_gray", bigGrayMeteoriteTexture));

	sf::Texture* largeBrownMeteoriteTexture = new sf::Texture();
	largeBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (large, brown).png");
	largeBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_large_brown", largeBrownMeteoriteTexture));

	sf::Texture* largeGrayMeteoriteTexture = new sf::Texture();
	largeGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (large, gray).png");
	largeGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_large_gray", largeGrayMeteoriteTexture));

	sf::Texture* middleBrownMeteoriteTexture = new sf::Texture();
	middleBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, brown).png");
	middleBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_middle_brown", middleBrownMeteoriteTexture));

	sf::Texture* middleGrayMeteoriteTexture = new sf::Texture();
	middleGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, gray).png");
	middleGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_middle_gray", middleGrayMeteoriteTexture));

	sf::Texture* smallBrownMeteoriteTexture = new sf::Texture();
	smallBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, brown).png");
	smallBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_small_brown", smallBrownMeteoriteTexture));

	sf::Texture* smallGrayMeteoriteTexture = new sf::Texture();
	smallGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, gray).png");
	smallGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_small_gray", smallGrayMeteoriteTexture));

	sf::Texture* endpointMarkerTexture = new sf::Texture();
	endpointMarkerTexture->loadFromFile("Resources/Sprites/Marker (endpoint).png");
	endpointMarkerTexture->setSmooth(isTexturesSmooth);
	this->markersTextures.insert(std::pair<std::string, sf::Texture*>("marker_ep", endpointMarkerTexture));
}

const std::map<std::string, sf::Texture*> CAssetsHelper::getMapTextures()
{
	return this->mapTextures;
}

const std::map<std::string, sf::Cursor*> CAssetsHelper::getCursors()
{
	return this->cursors;
}

sf::Texture* CAssetsHelper::getPlayerTexture()
{
	return this->playerTexture;
}

const std::map<std::string, sf::Texture*> CAssetsHelper::getMeteoritesTextures()
{
	return this->meteoritesTextures;
}

const std::map<std::string, sf::Texture*> CAssetsHelper::getMarkersTextures()
{
	return this->markersTextures;
}
