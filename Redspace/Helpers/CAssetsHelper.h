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

	/* ������ */
	std::map<std::string, sf::Font*> fonts;

	/* �������� ��� ����� */
	std::map<std::string, sf::Texture*> mapTextures;

	/* ������� */
	std::map<std::string, sf::Cursor*> cursors;

	/* �������� ������ */
	sf::Texture* playerTexture;

	/* �������� ���������� */
	std::map<std::string, sf::Texture*> meteoritesTextures;

	/* �������� �������� */
	std::map<std::string, sf::Texture*> markersTextures;

	/* �������� ����������� */
	std::map<std::string, sf::Texture*> enemiesTextures;

	/* �������� ���� */
	std::map<std::string, sf::Texture*> bulletsTextures;

public:
	/* ���������� ������������ ��������� �������� ������ � ������� �������� Singleton */
	static CAssetsHelper& getInstance();

	/* �������������� ��� ������� ���� */
	void configure(bool isTexturesSmooth = false);

	const std::map<std::string, sf::Font*>& getFonts();

	/* ���������� �������� ����� */
	const std::map<std::string, sf::Texture*> getMapTextures();

	/* ���������� ������� */
	const std::map<std::string, sf::Cursor*> getCursors();

	/* ���������� �������� ������ */
	sf::Texture* getPlayerTexture();

	/* ���������� �������� ���������� */
	const std::map<std::string, sf::Texture*> getMeteoritesTextures();

	/* ���������� �������� �������� */
	const std::map<std::string, sf::Texture*> getMarkersTextures();

	/* ���������� �������� ����������� */
	const std::map<std::string, sf::Texture*> getEnemiesTextures();

	/* ���������� �������� ���� */
	const std::map<std::string, sf::Texture*> getBulletsTextures();
};

#endif