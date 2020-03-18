#ifndef CASSETSHELPER_H
#define CASSETSHELPER_H

#include <vector>
#include <SFML/Graphics.hpp>

/* �����-�������� ��� ���������� ��������� ���� */
class CAssetsHelper
{
private:
	/* ��������������� �������� ������������ */
	CAssetsHelper() = default;

	/* ��������������� ������������ ����������� */
	CAssetsHelper(const CAssetsHelper& copy) = delete;

	/* ��������������� ��������� ���������� */
	CAssetsHelper& operator=(const CAssetsHelper&) = delete;

	/* �������� ����� */
	std::vector<sf::Texture*> mapTextures;

	/* �������� ������� */
	sf::Texture* crosshairTexture;

	/* �������� ������ */
	sf::Texture* playerTexture;

	/* �������� ���������� */
	std::vector<sf::Texture*> meteoritesTextures;

public:
	/* ���������� ������������ ��������� �������� ������ � ������� �������� Singleton */
	static CAssetsHelper& getInstance();

	/* �������������� ��� ������� ���� */
	void configure();

	/* ���������� �������� ����� */
	const std::vector<sf::Texture*> getMapTextures();

	/* ���������� �������� ������� */
	sf::Texture* getCrosshairTexture();

	/* ���������� �������� ������ */
	sf::Texture* getPlayerTexture();

	/* ���������� �������� ���������� */
	const std::vector<sf::Texture*> getMeteoritesTextures();
};

#endif