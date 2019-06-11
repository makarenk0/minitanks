#include "Endscreen.h"

Endscreen::Endscreen(bool isWon,int height, int width) {
	font.loadFromFile("assets\\ARCADECLASSIC.TTF");
	text.setFont(font);
	text.setCharacterSize(currentSize);
	tip.setFont(font);
	tip.setCharacterSize(42);
	tip.setOutlineColor(sf::Color::Green);
	tip.setFillColor(sf::Color::White);
	tip.setOutlineThickness(1);
	tip.setPosition(215, 600);
	tip.setString("press  ESCAPE  to  exit");
	canvas.create(height, width);
	if (isWon) {
		text.setString("CONGRATULATIONS");
		text.setPosition(185, 300);
	}
	else {
		text.setString("You failed\n  Try Again");
		text.setPosition(275, 250);
	}
	
	mainSprite.setTexture(canvas.getTexture(), false);
	mainSprite.setPosition(192.f, 0.f);
}

Endscreen::~Endscreen() {

}

void Endscreen::draw(sf::RenderWindow& window) {
	canvas.clear();
	if (increasing) {
		if (currentSize < 70) {
			currentSize+=0.8f;
			text.setCharacterSize(currentSize);
			text.setPosition(text.getPosition() - sf::Vector2f(0.8f, 0.8f));
		}
		else {
			increasing = !increasing;
		}
	}
	else if (!increasing) {
		if (currentSize > 55) {
			currentSize-=0.8f;
			text.setCharacterSize(currentSize);
			text.setPosition(text.getPosition() + sf::Vector2f(0.8f, 0.8f));
		}
		else {
			increasing = !increasing;
		}
	}
	canvas.draw(text);
	canvas.draw(tip);
	canvas.display();
	window.draw(mainSprite);
}