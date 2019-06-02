#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "TileMap.h"

#define FPS 60
#define width 1024
#define height 1024


int main() {
	sf::RenderWindow mWindow(sf::VideoMode(width, height), "Main window", sf::Style::Close | sf::Style::Titlebar);
	mWindow.setFramerateLimit(FPS);

	TileMap map("example_map.txt", 32, width, height, true);
	map.changeCurrentHealth(0, 0, -5);  //test of change health function
	map.changeCurrentHealth(35, 0, -4);
	map.changeCurrentHealth(67, 0, -3);
	map.changeCurrentHealth(100, 0, 0);


	//std::cout << map.checkCollisionOfPoint(36, 40);

	//for fps
	sf::Clock clock;
	float time;
	int fpscount = 0;
	//for fps

	while (mWindow.isOpen()) {
		
		time = clock.getElapsedTime().asSeconds();
		fpscount++;
		if (time >= 1) {
			clock.restart();
			system("cls");
			std::cout<<"fps:"<< fpscount;
			fpscount = 0;
		}
		

		sf::Event event;
		while (mWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				mWindow.close();
				break;}
			}

		}

		mWindow.clear();
		try {
			mWindow.draw(map);
		}
		catch (int i) {
			std::cout << i;
		}
		
		mWindow.display();
	}

	return 0;
}