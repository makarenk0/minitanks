#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Bullet {
protected:
  float speed;
  int direction;
  bool isSuper;
  sf::Sprite bulletSprite;
  sf::Texture bulletTexture;
  sf::Vector2f moveDir;
  sf::Vector2f position;
  void rotateSprite();

public:
  Bullet(sf::Vector2f position, int direction, const float speed, bool isSuper);
  float getSpeed();
  int getDirection();
  void updateBullet();
  void draw(sf::RenderWindow &window);
  void setTexture(sf::Texture &texture);
  ~Bullet();
};
