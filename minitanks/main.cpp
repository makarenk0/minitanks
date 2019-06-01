#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "TileMap.h"
#define FPS 60
#define width 1152
#define height 1024


int main() {
	sf::RenderWindow mWindow(sf::VideoMode(width, height), "Main window", sf::Style::Close | sf::Style::Titlebar);
	mWindow.setFramerateLimit(FPS);

	TileMap map("example_map.txt", 32, width, height);


	while (mWindow.isOpen()) {

		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				mWindow.close();
				break;}
			}

		}

		mWindow.clear();
		mWindow.draw(map);
		mWindow.display();
	}

	return 0;
}