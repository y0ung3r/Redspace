#ifndef CGAME_H
#define CGAME_H

enum GameStates;

/* �������� ����� ���� */
class CGame : public ex::EntityX
{
private:
	/* ������ �� ���� */
	sf::RenderWindow& target;

	/* ������� ������� ��������� */
	GameStates gameState;

public:
	/* ������� ����������� */
	explicit CGame(sf::RenderWindow& target);

	/* ������������ ������� SFML */
	void pollEvent(sf::Event event);

	/* ��������� ���� */
	void update(ex::TimeDelta timeDelta);

	/* ������ ������� ��������� */
	void setGameState(GameStates gameState);

	/* ���������� ������, ���� ���������� � �������� ��������� ������� ��������� �������� ������� */
	bool isGameState(GameStates gameState);

	/* ���������� ���������� ���� */
	static const sf::Vector2f& getMousePositionInCoords(sf::RenderWindow& target);
};

#endif