#ifndef CGAME_H
#define CGAME_H

class CGame;
enum GameStates;

/* Основной класс игры */
class CGame : public ex::EntityX
{
private:
	/* Текущее игровое состояние */
	static GameStates gameState;

	/* Ссылка на окно */
	sf::RenderWindow& target;

	/* Создает карту и возвращает ее идентификатор */
	ex::Entity::Id createMap();

	/* Создает объект камеры и возвращает его идентификатор */
	ex::Entity::Id createCamera();

	/* Создает игрока и возвращает его идентификатор */
	ex::Entity::Id createPlayer();

public:
	/* Базовый конструктор */
	explicit CGame(sf::RenderWindow& target);

	/* Обновляет игру */
	void update(ex::TimeDelta timeDelta);

	/* Возвращает истину, если текущее игровое состояние совпадает с переданным в качестве параметра */
	static bool isGameState(GameStates gameState);
};

#endif