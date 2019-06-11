#include "CollisionChecker.h"

std::vector<Enemy> vecEnemiesBuffer;
int accumulator;
const sf::Vector2f respawnPoint = sf::Vector2f(336.f, 672.f);

bool checkCollisionTiles(TileMap &map, Bullet bullet) {
    return map.checkTile(bullet.getGlobalBounds());
}

bool checkCollisionEnemies(Bullet bullet, std::vector<Enemy> &vecEnemies,
                           sf::Sound &hit, Widget &pl1, Widget &pl2) {
  vecEnemiesBuffer.clear();
  accumulator = 0;

  for (auto &i : vecEnemies) {

    if (bullet.getGlobalBounds().intersects(i.getGlobalBounds()) &&
        bullet.getWhose() != 0) {
      hit.play();
      i.decreaseHealth();
      if (i.getCurrentHealth() <= 0) {
		  i.~Enemy();
        if (bullet.getWhose()) {
          pl1.updateScore(pl1.getScore() + 1000);
        } else {
          pl2.updateScore(pl2.getScore() + 1000);
        }
      } else {
        vecEnemiesBuffer.push_back(i);
      }
      accumulator++;
    } else {
      vecEnemiesBuffer.push_back(i);
	  
    }
  }
  if (accumulator != 0)
    return true;
  else
    return false;
}

bool checkCollisionPlayers1(Bullet bullet, Player &pl1, sf::Sound &hit) {

  if (bullet.getGlobalBounds().intersects(pl1.getGlobalBounds())) {
    hit.play();
    pl1.decreaseHealth();
    if (pl1.getCurrentHealth() <= 0) {
      pl1.setPosition(respawnPoint);
      pl1.resetHealth();
    }
    return true;
  }
  return false;
}

/*void checkCollisionPlayers2(std::vector<Bullet> &vecBullets, Player &pl1,
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
}*/

std::vector<Enemy> getEnemies() { return vecEnemiesBuffer; }

void setEnemies(std::vector<Enemy> &newVector) {
	vecEnemiesBuffer = newVector;
}
