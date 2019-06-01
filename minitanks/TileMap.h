#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap(std::string FILE, int tileSize, int width, int height);
private:
	sf::VertexArray tiles;
	sf::Texture tileTexture;
	sf::Image image;
	int tileSize;
	int width;
	int height;
	std::ifstream file;
	std::string buf;
	int x;
	int y;
	int readValue(std::string str);
	double last;
	int id;

	bool solid;
	std::vector<std::vector<bool>> solidBool;
	std::vector<bool> buffer;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

