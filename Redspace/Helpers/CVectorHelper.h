#ifndef CVECTORHELPER_H
#define CVECTORHELPER_H

#include <SFML/Graphics.hpp>

/* „исло PI */
const float PI = 3.1415926535f;

/* —татический класс-помощник дл€ выполнени€ математических операций с векторами */
class CVectorHelper
{
private:
	/* ѕереопределение базового конструктора */
	CVectorHelper() = delete;

	/* ѕереопределение базового деструктора */
	~CVectorHelper() = delete;

public:
	template <typename T>
	/* ¬озвращает длину вектора */
	static float getLength(sf::Vector2<T>& valueA)
	{
		return sqrt(std::powf(valueA.x, 2) + std::powf(valueA.y, 2));
	}

	template <typename T>
	/* ¬озвращает рассто€ние между двум€ векторами */
	static float getDistance(sf::Vector2<T>& valueA, sf::Vector2<T>& valueB)
	{
		float lengthX = valueA.x - valueB.x;
		float lengthY = valueA.y - valueB.y;

		float sqrX = std::pow(lengthX, 2);
		float sqrY = std::pow(lengthY, 2);

		return std::sqrt(sqrX + sqrY);
	}

	template <typename T>
	/* ¬озвращает угол между двум€ векторами в радианах */
	static float getAngleInRadians(sf::Vector2<T>& valueA, sf::Vector2<T>& valueB)
	{
		float lengthX = valueA.x - valueB.x;
		float lengthY = valueA.y - valueB.y;

		return std::atan2(lengthY, lengthX);
	}

	template <typename T>
	/* ¬озвращает угол между двум€ векторами в градусах */
	static float getAngleInDegrees(sf::Vector2<T>& valueA, sf::Vector2<T>& valueB)
	{
		return CVectorHelper::getAngleInRadians<T>(valueA, valueB) * (180.0f / PI);
	}

	template <typename T>
	/* ¬озвращает орт вектора */
	static sf::Vector2<T> getOrt(sf::Vector2<T>& valueA)
	{
		return valueA * 1.0f / CVectorHelper::getLength(valueA);
	}

	template <typename T>
	/* ¬озвращает ортонормированный вектор */
	static sf::Vector2<T> toNormalized(sf::Vector2<T>& valueA)
	{
		sf::Vector2<T> ort = CVectorHelper::getOrt(valueA);

		return sf::Vector2<T>(roundf(ort.x), roundf(ort.y));
	}
};

#endif