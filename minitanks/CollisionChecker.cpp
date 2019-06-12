#include "CollisionChecker.h"

std::vector<Bullet> vec;

void checkCollisionTiles(TileMap &map, std::vector<Bullet> &vecBullets) {
  int indexI = 0;
  vec.clear();
  for (auto &i : vecBullets) {
    bool hit = map.checkTile(i.getGlobalBounds());
	if (!hit) {
		vec.push_back(i);
	}
	
    indexI++;
  }

 
}

std::vector<Enemy> checkCollisionEntities(std::vector<Bullet> &vecBullets,
                                          std::vector<Enemy> &vecEnt,
                                          sf::Sound &hit, Widget &widget) {

  int indexI = 0;
  int indexK = 0;
  for (auto &k : vecEnt) {

    for (auto &i : vecBullets) {

      if (i.getGlobalBounds().intersects(k.getGlobalBounds()) && i.getAlly() &&
          i.getReal()) {
        i.setReal(false);
        hit.play();
        k.setCurrentHealth();
        if (k.getCurrentHealth() <= 0) {
          k.~Enemy();
          std::vector<Enemy>::iterator it2 = vecEnt.begin() + indexK;
          vecEnt.erase(it2);
          widget.updateScore(1000);
          break;
        }
      }
      indexI++;
    }
    indexI = 0;
    indexK++;
  }
  vec = vecBullets;
  return vecEnt;
}

void checkCollisionPlayers2(std::vector<Bullet> &vecBullets, Player &pl1,
                            Player &pl2, sf::Sound &hit) {

  vec = vecBullets;
  int indexI = 0;

  for (auto &i : vecBullets) {

    if (i.getGlobalBounds().intersects(pl1.getGlobalBounds()) && i.getReal()) {
      i.setReal(false);
      hit.play();

      pl1.setCurrentHealth();
      if (pl1.getCurrentHealth() <= 0) {
        pl1.setPosition(sf::Vector2f(432.f, 700.f));
        pl1.resetHealth();
      }
    }
    indexI++;
  }
  indexI = 0;

  for (auto &i : vecBullets) {

    if (i.getGlobalBounds().intersects(pl2.getGlobalBounds()) && i.getReal()) {
      i.setReal(false);
      hit.play();

      pl2.setCurrentHealth();
      if (pl2.getCurrentHealth() <= 0) {
        pl2.setPosition(sf::Vector2f(432.f, 700.f));
        pl2.resetHealth();
      }
    }
    indexI++;
  }
  vec = vecBullets;
}

void checkCollisionPlayers1(std::vector<Bullet> &vecBullets, Player &pl1,
                            sf::Sound &hit) {

  vec = vecBullets;
  int indexI = 0;

  for (auto &i : vecBullets) {

    if (i.getGlobalBounds().intersects(pl1.getGlobalBounds()) && i.getReal()) {
      i.setReal(false);
      hit.play();

      pl1.setCurrentHealth();
      if (pl1.getCurrentHealth() <= 0) {
        pl1.setPosition(sf::Vector2f(336.f, 672.f));
        pl1.resetHealth();
      }
    }
    indexI++;
  }
  indexI = 0;

  vec = vecBullets;
}

std::vector<Bullet> getVector() { return vec; }
