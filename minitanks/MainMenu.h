#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
class MainMenu {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::RenderTexture canvas;
	sf::Image title;
	sf::Texture titleTexture,cursorTex, authorsTex;
	sf::Sprite cursor, titleSprite, mainSprite, authorsSprite;
	sf::Text option1, option2, option3;
	sf::Font font;
	int currentOption = 0;
	void redraw();

public:
	MainMenu(sf::Vector2f position,sf::Vector2i size);
	void draw(sf::RenderWindow& window);
	void nextOption();
	void previousOption();
	int getCurrentOption();
};