#pragma once
#include <SFML/Graphics.hpp>

class Endscreen {
private: 
	sf::Sprite mainSprite;
	sf::RenderTexture canvas;
	sf::Text text,tip;
	sf::Font font;
	bool isWon;
	float currentSize = 55.f;
	float currentAngle = 0;
	bool increasing = true;
public:
	Endscreen(bool isWon, int height, int width);
	~Endscreen();
	void draw(sf::RenderWindow& window);
};