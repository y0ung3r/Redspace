#ifndef CGAME_H
#define CGAME_H

enum GameStates;

/* Основной класс игры */
class CGame : public ex::EntityX
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Текущее игровое состояние */
	GameStates gameState;

	/* Создает карту и возвращает ее идентификатор */
	ex::Entity::Id createMap();

	/* Создает объект камеры и возвращает его идентификатор */
	ex::Entity::Id createCamera();

	/* Создает игрока и возвращает его идентификатор */
	ex::Entity::Id createPlayer();

public:
	/* Базовый конструктор */
	explicit CGame(sf::RenderWindow& target);

	/* Обрабатывает события SFML */
	void pollEvent(sf::Event event);

	/* Обновляет игру */
	void update(ex::TimeDelta timeDelta);

	/* Задает игровое состояние */
	void setGameState(GameStates gameState);

	/* Возвращает истину, если переданное в качестве аргумента игровое состояние является текущим */
	bool isGameState(GameStates gameState);

	/* Возвращает координаты мыши */
	static const sf::Vector2f& getMousePositionInCoords(sf::RenderWindow& target);
};

#endif