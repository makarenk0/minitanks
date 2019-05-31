#include "Renderer.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#define FPS 60

int main() {
	sf::RenderWindow mWindow(sf::VideoMode(1152, 1024), "Main window", sf::Style::Close | sf::Style::Titlebar);
	mWindow.setFramerateLimit(60);
	sf::Clock clock;
	sf::Sprite player1;

	sf::Sprite background;
	std::vector<sf::Sprite> vecSprite;

	
	sf::Texture back,p1;
	sf::Image image,pimage;
	image.create(63, 63, sf::Color::Green); //18x20
	pimage.create(32, 32, sf::Color::Red);
	p1.loadFromImage(pimage);
	player1.setTexture(p1);
	
	back.loadFromImage(image);
	background.setTexture(back);
	
	for (int i = 0; i < 370;++i) {
		sf::Sprite sprite;
		sprite.setTexture(back);
		vecSprite.push_back(sprite);
	}
	sf::RenderTexture test;
	test.draw(background);
	test.display();

	player1.setPosition(300, 300);
	float speedPlayer = 2;
	float time;
	float y=300;

	while (mWindow.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				mWindow.close();
				break;}
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			y += -speedPlayer * time;
		
			//player1.setPosition(0, y);
			player1.move(sf::Vector2f(0, -speedPlayer));
		}
		mWindow.clear();
		int k = 0;
		for (int i = 0;i < vecSprite.size();i++) {
			if (i % 20 == 0)
				k++;
			vecSprite[i].setPosition(i * 64 % 1152, k * 64 % 1024);
			mWindow.draw(vecSprite[i]);

		}
		
		mWindow.draw(player1);
		mWindow.display();

		//Render(mWindow, vecSprite,player1);
	}
	
	return 0;
}