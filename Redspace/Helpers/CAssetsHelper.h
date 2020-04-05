#ifndef CASSETSHELPER_H
#define CASSETSHELPER_H

class CAssetsHelper;

/* Класс-помощник для управления ресурсами игры */
class CAssetsHelper
{
private:
	/* Переопределение базового конструктора */
	CAssetsHelper() = default;

	/* Переопределение конструктора копирования */
	CAssetsHelper(const CAssetsHelper& copy) = delete;

	/* Переопределение оператора присвоения */
	CAssetsHelper& operator=(const CAssetsHelper&) = delete;

	/* Текстуры для карты */
	std::vector<sf::Texture*> mapTextures;

	/* Курсоры */
	std::vector<sf::Cursor*> cursors;

	/* Текстура игрока */
	sf::Texture* playerTexture;

	/* Текстуры метеоритов */
	std::vector<sf::Texture*> meteoritesTextures;

public:
	/* Возвращает единственный экземпляр текущего класса с помощью паттерна Singleton */
	static CAssetsHelper& getInstance();

	/* Инициализирует все ресурсы игры */
	void configure(bool isTexturesSmooth = false);

	/* Возвращает текстуры карты */
	const std::vector<sf::Texture*> getMapTextures();

	/* Возвращает курсоры */
	const std::vector<sf::Cursor*> getCursors();

	/* Возвращает текстуру игрока */
	sf::Texture* getPlayerTexture();

	/* Возвращает текстуры метеоритов */
	const std::vector<sf::Texture*> getMeteoritesTextures();
};

#endif