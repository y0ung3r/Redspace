#ifndef CASSETSHELPER_H
#define CASSETSHELPER_H

class CAssetsHelper;

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

	/* �������� ��� ����� */
	std::vector<sf::Texture*> mapTextures;

	/* ������� */
	std::vector<sf::Cursor*> cursors;

	/* �������� ������ */
	sf::Texture* playerTexture;

	/* �������� ���������� */
	std::vector<sf::Texture*> meteoritesTextures;

public:
	/* ���������� ������������ ��������� �������� ������ � ������� �������� Singleton */
	static CAssetsHelper& getInstance();

	/* �������������� ��� ������� ���� */
	void configure(bool isTexturesSmooth = false);

	/* ���������� �������� ����� */
	const std::vector<sf::Texture*> getMapTextures();

	/* ���������� ������� */
	const std::vector<sf::Cursor*> getCursors();

	/* ���������� �������� ������ */
	sf::Texture* getPlayerTexture();

	/* ���������� �������� ���������� */
	const std::vector<sf::Texture*> getMeteoritesTextures();
};

#endif