#include "Renderer.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#define FPS 60

int main() {
	sf::RenderWindow mWindow(sf::VideoMode(1152, 1024), "Main window", sf::Style::Close | sf::Style::Titlebar);



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
		mWindow.display();
	}
	
	return 0;
}