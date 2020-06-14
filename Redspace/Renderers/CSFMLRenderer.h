#ifndef CSFMLRENDERER_H
#define CSFMLRENDERER_H

#include "../Shapes/RoundedRectangleShape.h"

class CSFMLRenderer
{
private:
	sf::RenderWindow& target;

	const sf::Vector2f& translateToScreenCoordinates(const sf::Vector2f& point);

	sf::Text createText(const std::string& fontName, unsigned int fontSize, const std::string& text, const sf::Color& textColor);

	sf::RectangleShape createBox(const sf::Vector2f& size, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor);

	sf::RoundedRectangleShape createRoundedBox(const sf::Vector2f& size, float cornerRadius, const sf::Color& backgroundColor, float outlineThickness, const sf::Color& outlineColor);

public:
	CSFMLRenderer(sf::RenderWindow& target);

	void createGameText(const std::string& fontName, unsigned int fontSize, const std::string& text, const sf::Vector2f& position, const sf::Color& textColor = sf::Color::White);

	void createTextOnScreen(const std::string& fontName, unsigned int fontSize, const std::string& text, const sf::Vector2f& position, const sf::Color& textColor = sf::Color::White);

	void createGameBox(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& backgroundColor = sf::Color::White, float outlineThickness = 0.0f, const sf::Color& outlineColor = sf::Color::Transparent);

	void createBoxOnScreen(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& backgroundColor = sf::Color::White, float outlineThickness = 0.0f, const sf::Color& outlineColor = sf::Color::Transparent);

	void createGameRoundedBox(const sf::Vector2f& size, const sf::Vector2f& position, float cornerRadius = 1.0f, const sf::Color& backgroundColor = sf::Color::Transparent, float outlineThickness = 1.0f, const sf::Color& outlineColor = sf::Color::Black);

	void createRoundedBoxOnScreen(const sf::Vector2f& size, const sf::Vector2f& position, float cornerRadius = 1.0f, const sf::Color& backgroundColor = sf::Color::Transparent, float outlineThickness = 1.0f, const sf::Color& outlineColor = sf::Color::Black);
};

#endif