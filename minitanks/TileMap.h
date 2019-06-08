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

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(std::string FILE, int tileSize, int width, int height, bool randomMap, bool editMode);
	~TileMap();
	void changeCurrentHealth(int xPoint, int yPoint, int delta);
	bool checkCollisionOfPoint(int xPoint, int yPoint);
	bool getEditMode();
	void setEditMode(bool mode);
	void editMap(sf::RenderWindow &mWindow);
	void setExitEditMode(bool ex);
	void initMap(std::string FILE, int tileSize, int width, int height, bool randomMap, bool editMode);
	
private:
	
	sf::RenderWindow tools;
	sf::VertexArray tiles, overlay, toolsMenu, overlaysMenu;
	sf::Texture tileTexture, overlayTexture;
	int tileSize;
	int width;
	const int toolsWidth = 300, amountOfTools = 4;
	int height, toolsHeight;
	std::ifstream file;
	std::string buf;
	std::string fileName;
	int x;
	int y;
	int last;
	int id;
	int curHealth;
	bool solid;
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

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; // prefix "virtual" helps to call my overrided function "draw"()
	                                                                            // when i "window.draw(map)" this function is called
};

