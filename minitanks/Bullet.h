#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Bullet {
private:
  float speed;
  int direction;
  int whose;
  sf::Sprite bulletSprite;
  sf::Texture bulletTexture;
  sf::Vector2f moveDir;
  sf::Vector2f position;
  void rotateSprite();

public:
  Bullet(sf::Vector2f position, int direction, const float speed, int whose);
  int getWhose();
  float getSpeed();
  int getDirection();
  void updateBullet();
  void draw(sf::RenderWindow &window);
  void setTexture(sf::Texture &texture);
  sf::FloatRect getGlobalBounds();
  ~Bullet();
};
