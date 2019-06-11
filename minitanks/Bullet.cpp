#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f position, int direction, float speed, int whose) {
  this->speed = speed;
  this->direction = direction;
  this->position = position;
  this->whose = whose; // 0 - enemy, 1 - playerOne, 2 - playerTwo
  rotateSprite();
  bulletSprite.setPosition(position);
}

float Bullet::getSpeed() { return speed; }

int Bullet::getDirection() { return direction; }

void Bullet::updateBullet() { bulletSprite.move(moveDir); }

void Bullet::rotateSprite() {
  switch (direction) {
  case 0: {
    moveDir = {0.f, -speed};
    break;
  }
  case 1: {
    bulletSprite.rotate(90);
    moveDir = {speed, 0.f};
    break;
  }
  case 2: {
    bulletSprite.rotate(180);
    moveDir = {0.f, speed};
    break;
  }
  case 3: {
    bulletSprite.rotate(270);
    moveDir = {-speed, 0.f};
    break;
  }
  }
  bulletSprite.scale(0.7f, 0.7f);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(bulletSprite);
}

Bullet::~Bullet() {}

void Bullet::setTexture(sf::Texture &texture) {
  bulletSprite.setTexture(texture);
}

sf::FloatRect Bullet::getGlobalBounds() {
  return bulletSprite.getGlobalBounds();
}

int Bullet::getWhose()
{
	return whose;
}


