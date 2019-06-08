#include "MainMenu.h"
#define offset 130

void MainMenu::nextOption() {
	if (currentOption < 2) {
		std::cout << "next" << std::endl;
		currentOption++;
		cursor.setPosition(cursor.getPosition() + sf::Vector2f(0, offset));
		sound.play();
		redraw();
	}

}

void MainMenu::previousOption() {
	if (currentOption > 0 ) {
		std::cout << "prev" << std::endl;
		currentOption--;
		cursor.setPosition(cursor.getPosition() - sf::Vector2f(0, offset));
		sound.play();
		redraw();
	}
}

MainMenu::MainMenu(sf::Vector2f position, sf::Vector2i size) {
	//canvas creation
	canvas.create(size.x, size.y);
	canvas.clear({ 0,0,0,255 });
	mainSprite.setTexture(canvas.getTexture(), false);
	mainSprite.setPosition(position);
	//TITLE
	titleTexture.loadFromFile("assets\\Title.png");
	titleSprite.setTexture(titleTexture);
	titleSprite.setPosition(0, size.y / 10);
	//authors
	authorsTex.loadFromFile("assets\\Authors.png");
	authorsSprite.setTexture(authorsTex);
	authorsSprite.setPosition(size.x * 2 / 3-50.f, size.y *9/ 10);
	authorsSprite.scale(0.8f, 0.8f);
	//option init
	if (!font.loadFromFile("assets\\ARCADECLASSIC.TTF"))
		std::cout << "font load error" << std::endl;
	option1.setFont(font);
	option2.setFont(font);
	option3.setFont(font);
	option1.setFillColor(sf::Color::White);
	option2.setFillColor(sf::Color::White);
	option3.setFillColor(sf::Color::White);
	option1.setCharacterSize(50);
	option2.setCharacterSize(50);
	option3.setCharacterSize(50);
	option1.setString("1 PLAYER");
	option2.setString("2 PLAYERS");
	option3.setString("MAP EDITOR");
	option1.setPosition(canvas.getSize().x   / 3, canvas.getSize().y * 4 / 12+100);
	option2.setPosition(canvas.getSize().x  / 3, canvas.getSize().y * 6 / 12 + 100);
	option3.setPosition(canvas.getSize().x  / 3, canvas.getSize().y * 8 / 12 + 100);
	//cursor init
	cursorTex.loadFromFile("assets\\Player.png");
	cursor.setTexture(cursorTex);
	cursor.setPosition(option1.getPosition() - sf::Vector2f(75, -10));
	redraw();

	
	buffer.loadFromFile("assets\\select.wav");
	sound.setBuffer(buffer);
}

void MainMenu::draw(sf::RenderWindow& window) {
	window.draw(mainSprite);
}

int MainMenu::getCurrentOption() {
	return currentOption;
}

void MainMenu::redraw() {
	canvas.clear();
	canvas.draw(titleSprite);
	canvas.draw(authorsSprite);
	canvas.draw(option1);
	canvas.draw(option2);
	canvas.draw(option3);
	canvas.draw(cursor);
	canvas.display();
}