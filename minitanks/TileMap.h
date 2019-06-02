#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(std::string FILE, int tileSize, int width, int height, bool randomMap);
	~TileMap();
	void changeCurrentHealth(int xPoint, int yPoint, int delta);
	bool checkCollisionOfPoint(int xPoint, int yPoint);
private:
	sf::VertexArray tiles, overlay;
	sf::Texture tileTexture, overlayTexture;
	int tileSize;
	int width;
	int height;
	std::ifstream file;
	std::string buf;
	int x;
	int y;
	int last;
	int id;
	int curHealth;
	bool solid;

	std::vector<std::vector<bool>> solidBool;
	std::vector<std::vector<int>> currentHealth;

	std::string readValue(std::string str);
	void generateMapRandom();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // prefix "virtual" helps to call my overrided function "draw"()
	                                                                            // when i "window.draw(map)" this function is called
};

