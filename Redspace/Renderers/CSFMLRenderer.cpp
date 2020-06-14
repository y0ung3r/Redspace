#include <string>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

#include "../Helpers/CAssetsHelper.h"

#include "CSFMLRenderer.h"

CSFMLRenderer::CSFMLRenderer(sf::RenderWindow& target)
	: target(target)
{ }

const sf::Vector2f& CSFMLRenderer::translateToScreenCoordinates(const sf::Vector2f& point)
{
	sf::View targetView = this->target.getView();
	sf::Vector2f targetCenter = targetView.getCenter();
	sf::Vector2f targetSize = targetView.getSize();
	
	float left = targetCenter.x - targetSize.x / 2 + point.x;
	float top = targetCenter.y - targetSize.y / 2 + point.y;

	return sf::Vector2f(left, top);
}

sf::Text CSFMLRenderer::createText(const std::string& fontName, unsigned int fontSize, const std::string& text, const sf::Color& textColor)
{
	sf::Font* font = CAssetsHelper::getInstance().getFonts().at(fontName);

	sf::Text sfText(text, *font, fontSize);
	sfText.setFillColor(textColor);

	return sfText;
}

sf::RectangleShape CSFMLRenderer::createBox(const sf::Vector2f& size, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor)
{
	sf::RectangleShape sfBox;

	sfBox.setSize(size);
	sfBox.setFillColor(backgroundColor);
	sfBox.setOutlineThickness(outlineThickness);
	sfBox.setOutlineColor(outlineColor);

	return sfBox;
}

sf::RoundedRectangleShape CSFMLRenderer::createRoundedBox(const sf::Vector2f& size, float cornerRadius, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor)
{
	sf::RoundedRectangleShape sfRoundedBox;

	sfRoundedBox.setCornerPointCount(4);
	sfRoundedBox.setSize(size);
	sfRoundedBox.setCornersRadius(cornerRadius);
	sfRoundedBox.setFillColor(backgroundColor);
	sfRoundedBox.setOutlineThickness(outlineThickness);
	sfRoundedBox.setOutlineColor(outlineColor);

	return sfRoundedBox;
}

void CSFMLRenderer::createGameText(const std::string& fontName, unsigned int fontSize, const std::string& text, const sf::Vector2f& position, const sf::Color& textColor)
{
	sf::Text sfText = createText(fontName, fontSize, text, textColor);

	sfText.setPosition(position);

	this->target.draw(sfText);
}

void CSFMLRenderer::createTextOnScreen(const std::string& fontName, unsigned int fontSize, const std::string& text, const sf::Vector2f& position, const sf::Color& textColor)
{
	sf::Text sfText = createText(fontName, fontSize, text, textColor);

	sf::Vector2f screenPosition = translateToScreenCoordinates(position);
	sfText.setPosition(screenPosition);

	this->target.draw(sfText);
}

void CSFMLRenderer::createGameBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor)
{
	sf::RectangleShape sfBox = createBox(size, backgroundColor, outlineThickness, outlineColor);

	sfBox.setPosition(position);

	this->target.draw(sfBox);
}

void CSFMLRenderer::createBoxOnScreen(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor)
{
	sf::RectangleShape sfBox = createBox(size, backgroundColor, outlineThickness, outlineColor);

	sf::Vector2f screenPosition = translateToScreenCoordinates(position);
	sfBox.setPosition(screenPosition);

	this->target.draw(sfBox);
}

void CSFMLRenderer::createGameRoundedBox(const sf::Vector2f& size, const sf::Vector2f& position, float cornerRadius, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor)
{
	sf::RoundedRectangleShape sfRoundedBox = createRoundedBox(size, cornerRadius, backgroundColor, outlineThickness, outlineColor);

	sfRoundedBox.setPosition(position);

	this->target.draw(sfRoundedBox);
}

void CSFMLRenderer::createRoundedBoxOnScreen(const sf::Vector2f& size, const sf::Vector2f& position, float cornerRadius, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor)
{
	sf::RoundedRectangleShape sfRoundedBox = createRoundedBox(size, cornerRadius, backgroundColor, outlineThickness, outlineColor);

	sf::Vector2f screenPosition = translateToScreenCoordinates(position);
	sfRoundedBox.setPosition(screenPosition);

	this->target.draw(sfRoundedBox);
}