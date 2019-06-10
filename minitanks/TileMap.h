#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "toolbox.h"

/*
health meanings:
health [0, 3] is different types of brick cells, when they are damaged
health = 4 means that this cell could not be damaged
health = 5 special condition, means that over the ground cell it is a bush
*/

class TileMap
{
public:
	TileMap();
	TileMap(std::string FILE, int tileSize, int width, int height, int widgetWidth, bool randomMap, bool editMode, int playersNum);
	void changeCurrentHealth(int xPoint, int yPoint, int delta);
	bool checkCollisionOfPoint(int xPoint, int yPoint);
	bool getEditMode();
	void setEditMode(bool mode);
	void editMap(sf::RenderWindow& mWindow);
	void setExitEditMode(bool ex);
	void initMap(std::string FILE, int tileSize, int width, int height, int widgetWidth, bool randomMap, bool editMode, int plauersNum);
	void draw(sf::RenderWindow& window);
	void setFirstLayer(bool set);
	int widgetWidth;
	int pl1X, pl1Y, pl2X, pl2Y;
	int height, width;
	bool checkTile(sf::FloatRect bullet);
	sf::Sprite allieBase, enemyBase;
	bool win = false, fail = false;
	std::vector<sf::Vector2f> enemiesCords;
private:
	std::vector<sf::Sprite> enemiesEditMap;
	int counterE = 0;
	bool enemyBasePresent = false, allieBasePresent = false;
	sf::RenderTexture canvas, canvasOverlay, canvasPlayers;
	sf::Texture aliesB;
	sf::Texture enemyB;
	sf::Texture enemy;
	sf::Sprite pl1Edit, pl2Edit, mapPl1, mapPl2;
	sf::Sprite allieBaseEdit, enemyBaseEdit, enemySprite, enemySprEdit;
	bool pl1EditPlaced = false, pl2EditPlaced = false, allieBasePlaced = false, enemyBasePlaced = false, setEnemies;
	sf::Texture pl1Text, pl2Text;
	sf::Texture allieBaseEditTex;
	sf::Texture enemyBaseEditTex;
	sf::Sprite mainSprite, overlaySprite, playersSprite;
	sf::RenderWindow tools;
	sf::VertexArray tiles, overlay, toolsMenu, overlaysMenu;
	sf::Texture tileTexture, overlayTexture;
	int tileSize;
	int toolsWidth, amountOfTools = 4;
	int toolsHeight = 80;
	std::ifstream file;
	std::string buf;
	std::string fileName;
	std::string toFile;
	int x;
	int y;
	int last;
	int id;
	int curHealth;
	bool solid, firstLayer;
	bool editMode, exitEditMode;
	int previousX = 0, previousY = 0;
	int playersNum;
	std::string fromFile;



	std::vector<std::vector<bool>> solidBool;
	std::vector<std::vector<int>> currentHealth;

	//for editor
	int idEdit = 0;
	int healthEdit = 4;
	bool solEdit = false;
	const int vert = 4;
	//for editor

	std::string readValue(std::string str);
	void generateMapRandom();
	void generateMapEmpty();
	void openEditWindow();
	void drawToolWindow(int winX, int winY);
	void changeTile(int x, int y);

};

