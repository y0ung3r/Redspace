#ifndef CGAME_H
#define CGAME_H

enum GameStates;

#include "../Renderers/CSFMLRenderer.h"
#include "../Interfaces/IObjectFactory.h"

/* Основной класс игры */
class CGame : public ex::EntityX, public ex::Receiver<CGame>
{
private:
	/* Ссылка на окно */
	sf::RenderWindow& target;

	float fps;

	CSFMLRenderer* SFMLRenderer;

	// В будущем необходимо не передавать в системы указатели на фабрики, а получать их из экземляра класса
	// И вообще надо сделать оптимизацию кода :)
	IObjectFactory* mapFactory;

	IObjectFactory* cameraFactory;

	IObjectFactory* playerFactory;

	IObjectFactory* bulletFactory;

	IObjectFactory* enemyFactory;

	IObjectFactory* effectFactory;

	IObjectFactory* meteoriteFactory;

	ex::Entity::Id mapId;

	ex::Entity::Id cameraId;

	ex::Entity::Id playerId;

	/* Текущее игровое состояние */
	GameStates gameState;

public:
	/* Базовый конструктор */
	explicit CGame(sf::RenderWindow& target);

	/* Обрабатывает события SFML */
	void pollEvent(sf::Event event);

	/* Обновляет игру */
	void update(ex::TimeDelta timeDelta, sf::Time elapsedTime);

	float getFPS();

	CSFMLRenderer* getSFMLRenderer();

	ex::Entity::Id getCameraId();

	ex::Entity::Id getMapId();

	ex::Entity::Id getPlayerId();

	/* Задает игровое состояние */
	void setGameState(GameStates gameState);

	/* Возвращает истину, если переданное в качестве аргумента игровое состояние является текущим */
	bool isGameState(GameStates gameState);

	/* Возвращает координаты мыши */
	static const sf::Vector2f& getMousePositionInCoords(sf::RenderWindow& target);

	void receive(const ex::EntityDestroyedEvent& entityDestroyedEvent);
};

#endif