#ifndef CVECTORHELPER_H
#define CVECTORHELPER_H

#include <SFML/Graphics.hpp>

/* Число PI */
const float PI = 3.1415926535f;

/* Класс-помощник для выполнения математических операций с векторами */
class CVectorHelper
{
public:
	template <typename T>
	/* Возвращает длину вектора */
	float getLength(sf::Vector2<T>& valueA)
	{
		return sqrt(std::powf(valueA.x, 2) + std::powf(valueA.y, 2));
	}

	template <typename T>
	/* Возвращает расстояние между двумя векторами */
	float getDistance(sf::Vector2<T>& valueA, sf::Vector2<T>& valueB)
	{
		float lengthX = valueA.x - valueB.x;
		float lengthY = valueA.y - valueB.y;

		float sqrX = std::pow(lengthX, 2);
		float sqrY = std::pow(lengthY, 2);

		return std::sqrt(sqrX + sqrY);
	}

	template <typename T>
	/* Возвращает угол между двумя векторами в радианах */
	float getAngleInRadians(sf::Vector2<T>& valueA, sf::Vector2<T>& valueB)
	{
		float lengthX = valueA.x - valueB.x;
		float lengthY = valueA.y - valueB.y;

		return std::atan2(lengthY, lengthX);
	}

	template <typename T>
	/* Возвращает угол между двумя векторами в градусах */
	float getAngleInDegrees(sf::Vector2<T>& valueA, sf::Vector2<T>& valueB)
	{
		return CVectorHelper::getAngleInRadians<T>(valueA, valueB) * (180.0f / PI);
	}

	template <typename T>
	/* Возвращает орт вектора */
	sf::Vector2<T> getOrt(sf::Vector2<T>& valueA)
	{
		return valueA * 1.0f / CVectorHelper::getLength(valueA);
	}
};

#endif