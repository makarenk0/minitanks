#include "Renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "TileMap.h"
#include "Player.h"

#define FPS 60
#define width 800
#define height 608
#define cellWidth 32


int main() {
	sf::RenderWindow mWindow(sf::VideoMode(width, height), "Main window", sf::Style::Close | sf::Style::Titlebar);
	
	mWindow.setFramerateLimit(FPS);

	TileMap map("example_map", cellWidth, width, height, false, false);
	Player pl("Player.png", 13, 13, 26, 26, 2, 1, cellWidth, &map);
	
//	map.changeCurrentHealth(0, 0, -5);  //test of change health function
//	map.changeCurrentHealth(35, 0, -4);
//	map.changeCurrentHealth(67, 0, -3);
//	map.changeCurrentHealth(100, 0, 0);


	std::cout << map.checkCollisionOfPoint(416, 160);

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

		//for map
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {  //this event is when user press "editor" to create own map
			map.initMap("example_map", cellWidth, width, height, false, true);
		}
		if (map.getEditMode()) {   //checking if user switched to editor mod
			map.editMap(mWindow);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {  //this event is when user press "exit" from editor
				map.setExitEditMode(true);
			}
		}
		//for map

		pl.updatePlayer();
		mWindow.draw(map);
		mWindow.draw(pl);
		
		
		mWindow.display();
	}

	return 0;
}