#ifndef CVECTORHELPER_H
#define CVECTORHELPER_H

class CVectorHelper;

/* Число PI */
const float PI = 3.1415926535f;

/* Класс-помощник для выполнения математических операций с векторами */
class CVectorHelper
{
public:
	template <typename T>
	/* Возвращает длину вектора */
	float getLength(sf::Vector2<T>& vector)
	{
		return std::hypotf(vector.x, vector.y);
	}

	template <typename T>
	/* Возвращает расстояние между двумя векторами */
	float getDistance(sf::Vector2<T>& from, sf::Vector2<T>& to)
	{
		sf::Vector2<T> difference = from - to;

		return std::hypotf(difference.x, difference.y);
	}

	template <typename T>
	/* Возвращает угол между двумя векторами в радианах */
	float getAngleInRadians(sf::Vector2<T>& from, sf::Vector2<T>& to)
	{
		sf::Vector2<T> difference = from - to;

		return std::atan2f(difference.y, difference.x) + PI;
	}

	template <typename T>
	/* Возвращает угол между двумя векторами в градусах */
	float getAngleInDegrees(sf::Vector2<T>& from, sf::Vector2<T>& to)
	{
		return CVectorHelper::getAngleInRadians<T>(from, to) * (180.0f / PI);
	}

	template <typename T>
	/* Возвращает орт вектора */
	sf::Vector2<T> getOrt(sf::Vector2<T>& vector)
	{
		return vector / CVectorHelper::getLength(vector);
	}
};

#endif