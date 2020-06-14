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
	sf::Font* kenVectorFont = new sf::Font();
	kenVectorFont->loadFromFile("Resources/Fonts/KenVector.ttf");
	this->fonts.insert(std::pair<std::string, sf::Font*>("kenVector", kenVectorFont));
	
	sf::Font* tahomaFont = new sf::Font();
	tahomaFont->loadFromFile("Resources/Fonts/Tahoma.ttf");
	this->fonts.insert(std::pair<std::string, sf::Font*>("tahoma", tahomaFont));

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

	sf::Texture* cursorCrosshairAttackTexture = new sf::Texture();
	cursorCrosshairAttackTexture->loadFromFile("Resources/Sprites/Cursor (crosshair, attack).png");
	cursorCrosshairAttackTexture->setSmooth(isTexturesSmooth);
	sf::Image cursorCrosshairAttackImage = cursorCrosshairAttackTexture->copyToImage();
	const sf::Uint8* cursorCrosshairAttackPixels = cursorCrosshairAttackImage.getPixelsPtr();
	sf::Cursor* cursorCrosshairAttack = new sf::Cursor();
	sf::Vector2u cursorCrosshairAttackSize = cursorCrosshairAttackTexture->getSize();
	sf::Vector2u cursorCrosshairAttackHotspot = sf::Vector2u();
	cursorCrosshairAttackHotspot.x = cursorCrosshairAttackSize.x / 2;
	cursorCrosshairAttackHotspot.y = cursorCrosshairAttackSize.y / 2;
	cursorCrosshairAttack->loadFromPixels(cursorCrosshairAttackPixels, cursorCrosshairAttackSize, cursorCrosshairAttackHotspot);
	this->cursors.insert(std::pair<std::string, sf::Cursor*>("csr_crosshair_attack", cursorCrosshairAttack));

	sf::Texture* cursorCrosshairHoverTexture = new sf::Texture();
	cursorCrosshairHoverTexture->loadFromFile("Resources/Sprites/Cursor (crosshair, hover).png");
	cursorCrosshairHoverTexture->setSmooth(isTexturesSmooth);
	sf::Image cursorCrosshairHoverImage = cursorCrosshairHoverTexture->copyToImage();
	const sf::Uint8* cursorCrosshairHoverPixels = cursorCrosshairHoverImage.getPixelsPtr();
	sf::Cursor* cursorCrosshairHover = new sf::Cursor();
	sf::Vector2u cursorCrosshairHoverSize = cursorCrosshairHoverTexture->getSize();
	sf::Vector2u cursorCrosshairHoverHotspot = sf::Vector2u();
	cursorCrosshairHoverHotspot.x = cursorCrosshairHoverSize.x / 2;
	cursorCrosshairHoverHotspot.y = cursorCrosshairHoverSize.y / 2;
	cursorCrosshairHover->loadFromPixels(cursorCrosshairHoverPixels, cursorCrosshairHoverSize, cursorCrosshairHoverHotspot);
	this->cursors.insert(std::pair<std::string, sf::Cursor*>("csr_crosshair_hover", cursorCrosshairHover));

	sf::Texture* playerTexture = new sf::Texture();
	playerTexture->loadFromFile("Resources/Sprites/Player.png");
	playerTexture->setSmooth(isTexturesSmooth);
	this->playerTexture = playerTexture;

	sf::Texture* bigBrownMeteoriteTexture = new sf::Texture();
	bigBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, brown).png");
	bigBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_0", bigBrownMeteoriteTexture));

	sf::Texture* bigGrayMeteoriteTexture = new sf::Texture();
	bigGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (big, gray).png");
	bigGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_1", bigGrayMeteoriteTexture));

	sf::Texture* largeBrownMeteoriteTexture = new sf::Texture();
	largeBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (large, brown).png");
	largeBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_2", largeBrownMeteoriteTexture));

	sf::Texture* largeGrayMeteoriteTexture = new sf::Texture();
	largeGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (large, gray).png");
	largeGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_3", largeGrayMeteoriteTexture));

	sf::Texture* middleBrownMeteoriteTexture = new sf::Texture();
	middleBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, brown).png");
	middleBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_4", middleBrownMeteoriteTexture));

	sf::Texture* middleGrayMeteoriteTexture = new sf::Texture();
	middleGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (middle, gray).png");
	middleGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_5", middleGrayMeteoriteTexture));

	sf::Texture* smallBrownMeteoriteTexture = new sf::Texture();
	smallBrownMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, brown).png");
	smallBrownMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_6", smallBrownMeteoriteTexture));

	sf::Texture* smallGrayMeteoriteTexture = new sf::Texture();
	smallGrayMeteoriteTexture->loadFromFile("Resources/Sprites/Meteorite (small, gray).png");
	smallGrayMeteoriteTexture->setSmooth(isTexturesSmooth);
	this->meteoritesTextures.insert(std::pair<std::string, sf::Texture*>("meteorite_7", smallGrayMeteoriteTexture));

	sf::Texture* endpointMarkerTexture = new sf::Texture();
	endpointMarkerTexture->loadFromFile("Resources/Sprites/Marker (endpoint).png");
	endpointMarkerTexture->setSmooth(isTexturesSmooth);
	this->markersTextures.insert(std::pair<std::string, sf::Texture*>("marker_ep", endpointMarkerTexture));

	sf::Texture* enemyTexture = new sf::Texture();
	enemyTexture->loadFromFile("Resources/Sprites/Enemy.png");
	enemyTexture->setSmooth(isTexturesSmooth);
	this->enemiesTextures.insert(std::pair<std::string, sf::Texture*>("enemy", enemyTexture));

	sf::Texture* bulletBlueTexture = new sf::Texture();
	bulletBlueTexture->loadFromFile("Resources/Sprites/Bullet (blue).png");
	bulletBlueTexture->setSmooth(isTexturesSmooth);
	this->bulletsTextures.insert(std::pair<std::string, sf::Texture*>("bullet_blue", bulletBlueTexture));

	sf::Texture* bulletRedTexture = new sf::Texture();
	bulletRedTexture->loadFromFile("Resources/Sprites/Bullet (red).png");
	bulletRedTexture->setSmooth(isTexturesSmooth);
	this->bulletsTextures.insert(std::pair<std::string, sf::Texture*>("bullet_red", bulletRedTexture));

	sf::Texture* bulletHitTexture = new sf::Texture();
	bulletHitTexture->loadFromFile("Resources/Sprites/Bullet (hit).png");
	bulletHitTexture->setSmooth(isTexturesSmooth);
	this->bulletsTextures.insert(std::pair<std::string, sf::Texture*>("bullet_hit", bulletHitTexture));
}

const std::map<std::string, sf::Font*>& CAssetsHelper::getFonts()
{
	return this->fonts;
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

const std::map<std::string, sf::Texture*> CAssetsHelper::getEnemiesTextures()
{
	return this->enemiesTextures;
}

const std::map<std::string, sf::Texture*> CAssetsHelper::getBulletsTextures()
{
	return this->bulletsTextures;
}
