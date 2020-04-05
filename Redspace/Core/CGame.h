#ifndef CGAME_H
#define CGAME_H

class CGame;
enum GameStates;

/* �������� ����� ���� */
class CGame : public ex::EntityX
{
private:
	/* ������� ������� ��������� */
	static GameStates gameState;

	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������� ����� � ���������� �� ������������� */
	ex::Entity::Id createMap();

	/* ������� ������ ������ � ���������� ��� ������������� */
	ex::Entity::Id createCamera();

	/* ������� ������ � ���������� ��� ������������� */
	ex::Entity::Id createPlayer();

public:
	/* ������� ����������� */
	explicit CGame(sf::RenderWindow& target);

	/* ��������� ���� */
	void update(ex::TimeDelta timeDelta);

	/* ���������� ������, ���� ������� ������� ��������� ��������� � ���������� � �������� ��������� */
	static bool isGameState(GameStates gameState);
};

#endif