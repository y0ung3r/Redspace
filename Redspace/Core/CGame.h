#ifndef CGAME_H
#define CGAME_H

enum GameStates;

#include "../Interfaces/IObjectFactory.h"

/* �������� ����� ���� */
class CGame : public ex::EntityX, public ex::Receiver<CGame>
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	float fps;

	IObjectFactory* mapFactory;

	IObjectFactory* cameraFactory;

	IObjectFactory* playerFactory;

	IObjectFactory* bulletFactory;

	IObjectFactory* enemyFactory;

	ex::Entity::Id mapId;

	ex::Entity::Id cameraId;

	ex::Entity::Id playerId;

	/* ������� ������� ��������� */
	GameStates gameState;

public:
	/* ������� ����������� */
	explicit CGame(sf::RenderWindow& target);

	/* ������������ ������� SFML */
	void pollEvent(sf::Event event);

	/* ��������� ���� */
	void update(ex::TimeDelta timeDelta, sf::Time elapsedTime);

	float getFPS();

	ex::Entity::Id getCameraId();

	ex::Entity::Id getMapId();

	ex::Entity::Id getPlayerId();

	/* ������ ������� ��������� */
	void setGameState(GameStates gameState);

	/* ���������� ������, ���� ���������� � �������� ��������� ������� ��������� �������� ������� */
	bool isGameState(GameStates gameState);

	/* ���������� ���������� ���� */
	static const sf::Vector2f& getMousePositionInCoords(sf::RenderWindow& target);

	void receive(const ex::EntityDestroyedEvent& entityDestroyedEvent);
};

#endif