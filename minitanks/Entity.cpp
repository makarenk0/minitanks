#include "Entity.h"

Entity::Entity(int x, int y, int w, int h, int dir, std::string file, int speed,
	int tileSize, TileMap* map, int maxHealth) {

	widgetWidth = map->widgetWidth;
	this->x = x;
	this->y = y;
	this->w = w * 0.8f;
	this->h = h * 0.8f;
	this->speed = speed;
	this->tileSize = tileSize;
	this->dir = dir;
	this->map = map;
	this->maxHealth = maxHealth;
	this->currentHealth = maxHealth;
	if (file != "ENEMY") {
		entityTexture.loadFromFile("assets/" + file);
		entitySprite.setTexture(entityTexture);
	}

	entitySprite.setOrigin((w / 2), (h / 2));
	entitySprite.setPosition(x + widgetWidth, y);
	entitySprite.scale(0.8f, 0.8f);

	switch (dir) {
	case 0: {

		break;
	}
	case 1: {
		entitySprite.rotate(90);

		break;
	}
	case 2: {
		entitySprite.rotate(180);

		break;
	}
	case 3: {
		entitySprite.rotate(270);

		break;
	}
	}
}

void Entity::initEntity(int x, int y, int w, int h, int dir, std::string file,
	int speed, int tileSize, TileMap * map, int maxHealth) {
	widgetWidth = map->widgetWidth;
	this->x = x;
	this->y = y;
	this->w = w * 0.8f;
	this->h = h * 0.8f;
	this->speed = speed;
	this->tileSize = tileSize;
	this->dir = dir;
	this->map = map;
	this->maxHealth = maxHealth;
	this->currentHealth = maxHealth;

	if (file != "ENEMY") {
		entityTexture.loadFromFile("assets/" + file);
		entitySprite.setTexture(entityTexture);
	}
	entitySprite.setOrigin((w / 2), (h / 2));
	entitySprite.setPosition(x + widgetWidth, y);
	entitySprite.setScale(0.8f, 0.8f);

	switch (dir) {
	case 0: {

		break;
	}
	case 1: {
		entitySprite.rotate(90);

		break;
	}
	case 2: {
		entitySprite.rotate(180);

		break;
	}
	case 3: {
		entitySprite.rotate(270);

		break;
	}
	}
}

void Entity::update() {

	switch (dir) {
	case 0:
		dx = 0;
		dy = -speed;
		break;
	case 1:
		dx = speed;
		dy = 0;
		break;
	case 2:
		dx = 0;
		dy = speed;
		break;
	case 3:
		dx = -speed;
		dy = 0;
		break;
	}
	speed = 0;
	entitySprite.move(dx, dy);
	x += dx;
	y += dy;
	interactMap();
}

void Entity::setSpeed(int speed) { this->speed = speed; }

void Entity::interactMap() {
	// map bounds

	if (y < (h / 2)) {
		y = (h / 2);
		entitySprite.setPosition(widgetWidth + x, y);
		collisions++;
	}
	if (y > map->height - (h / 2)) {
		y = map->height - (h / 2);
		entitySprite.setPosition(widgetWidth + x, y);
		collisions++;
	}
	if (x < (w / 2)) {
		x = w / 2;
		entitySprite.setPosition(widgetWidth + x, y);
		collisions++;
	}
	if (x > map->width - (w / 2)) {
		x = map->width - (w / 2);
		entitySprite.setPosition(widgetWidth + x, y);
		collisions++;
	}
	// tile bounds
	for (int i = (y - (h / 2) + rangeBetweenTiles) / tileSize;
		i <= ((y + (h / 2) - rangeBetweenTiles) / tileSize); i++) {
		for (int j = (x - (w / 2) + rangeBetweenTiles) / tileSize;
			j <= ((x + (w / 2) - rangeBetweenTiles) / tileSize); j++) {
			if (map->checkCollisionOfPoint(j * tileSize, i * tileSize, false)) {
				collisions++;
				if (dy > 0) {

					y = i * tileSize - h / 2 - 1 + rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth + x, y);
				}
				if (dy < 0) {
					y = (i * tileSize) + tileSize + h / 2 - rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth + x, y);
				}
				if (dx > 0) {
					x = j * tileSize - w / 2 - 1 + rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth + x, y);
				}
				if (dx < 0) {
					x = j * tileSize + tileSize + w / 2 - rangeBetweenTiles;
					entitySprite.setPosition(widgetWidth + x, y);
				}
			}
		}
	}
	if (collisions == 0) {
		frontBlocked = false;

	}
	else {
		frontBlocked = true;
		collisions = 0;
	}
}

sf::Vector2f Entity::getFacePosition() {

	switch (dir) {
	case 0: {
		return sf::Vector2f(entitySprite.getPosition().x - 7,
			entitySprite.getPosition().y - 50);
		break;
	}
	case 1: {
		return sf::Vector2f(entitySprite.getPosition().x +
			entitySprite.getGlobalBounds().width + 15,
			entitySprite.getPosition().y - 7);
		break;
	}
	case 2: {
		return sf::Vector2f(entitySprite.getPosition().x + 7,
			entitySprite.getPosition().y +
			entitySprite.getGlobalBounds().height + 15);
		break;
	}
	case 3: {
		return sf::Vector2f(entitySprite.getPosition().x - 50,
			entitySprite.getPosition().y + 7);
		break;
	}
	}
}

int Entity::getDirection() { return dir; }

sf::FloatRect Entity::getGlobalBounds() {
	return entitySprite.getGlobalBounds();
}

void Entity::draw(sf::RenderWindow & window) { window.draw(entitySprite); }

int Entity::getCurrentHealth() { return currentHealth; }

void Entity::decreaseHealth() { currentHealth -= 1; }

void Entity::resetHealth() { currentHealth = maxHealth; }
Entity::~Entity() {}

Entity::Entity() {}

void Entity::setEnemyTexture(sf::Texture & tex) {
	entitySprite.setTexture(tex);
}
