#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include<thread>

/*
health meanings:
health [0, 3] is different types of brick cells, when they are damaged
health = 4 means that this cell could not be damaged
health = 5 special condition, means that over the ground cell it is a bush
*/

class TileMap
{
public:
	TileMap(std::string FILE, int tileSize, int width, int height, int widgetWidth, bool randomMap, bool editMode);
	~TileMap();
	void changeCurrentHealth(int xPoint, int yPoint, int delta);
	bool checkCollisionOfPoint(int xPoint, int yPoint);
	bool getEditMode();
	void setEditMode(bool mode);
	void editMap(sf::RenderWindow &mWindow);
	void setExitEditMode(bool ex);
	void initMap(std::string FILE, int tileSize, int width, int height, bool randomMap, bool editMode);
	void draw(sf::RenderWindow& window);
	void setFirstLayer(bool set);

	int widgetWidth;
private:
	sf::RenderTexture canvas, canvasOverlay;
	sf::Sprite mainSprite, overlaySprite;
	sf::RenderWindow tools;
	sf::VertexArray tiles, overlay, toolsMenu, overlaysMenu;
	sf::Texture tileTexture, overlayTexture;
	int tileSize;
	int width;
	int toolsWidth, amountOfTools = 4;
	int height, toolsHeight = 80;
	std::ifstream file;
	std::string buf;
	std::string fileName;
	int x;
	int y;
	int last;
	int id;
	int curHealth;
	bool solid, firstLayer;
	bool editMode, exitEditMode;
	int previousX=0, previousY=0;

	

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

