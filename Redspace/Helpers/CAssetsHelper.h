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

	/* Шрифты */
	std::map<std::string, sf::Font*> fonts;

	/* Текстуры для карты */
	std::map<std::string, sf::Texture*> mapTextures;

	/* Курсоры */
	std::map<std::string, sf::Cursor*> cursors;

	/* Текстура игрока */
	sf::Texture* playerTexture;

	/* Текстуры метеоритов */
	std::map<std::string, sf::Texture*> meteoritesTextures;

	/* Текстуры маркеров */
	std::map<std::string, sf::Texture*> markersTextures;

	/* Текстуры противников */
	std::map<std::string, sf::Texture*> enemiesTextures;

	/* Текстуры пуль */
	std::map<std::string, sf::Texture*> bulletsTextures;

public:
	/* Возвращает единственный экземпляр текущего класса с помощью паттерна Singleton */
	static CAssetsHelper& getInstance();

	/* Инициализирует все ресурсы игры */
	void configure(bool isTexturesSmooth = false);

	const std::map<std::string, sf::Font*>& getFonts();

	/* Возвращает текстуры карты */
	const std::map<std::string, sf::Texture*> getMapTextures();

	/* Возвращает курсоры */
	const std::map<std::string, sf::Cursor*> getCursors();

	/* Возвращает текстуру игрока */
	sf::Texture* getPlayerTexture();

	/* Возвращает текстуры метеоритов */
	const std::map<std::string, sf::Texture*> getMeteoritesTextures();

	/* Возвращает текстуры маркеров */
	const std::map<std::string, sf::Texture*> getMarkersTextures();

	/* Возвращает текстуры противников */
	const std::map<std::string, sf::Texture*> getEnemiesTextures();

	/* Возвращает текстуры пуль */
	const std::map<std::string, sf::Texture*> getBulletsTextures();
};

#endif