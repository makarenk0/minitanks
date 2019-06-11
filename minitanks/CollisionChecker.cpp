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

bool checkCollisionPlayer(Bullet bullet, Player &player, sf::Sound &hit) {

  if (bullet.getGlobalBounds().intersects(player.getGlobalBounds())) {
    hit.play();
	player.decreaseHealth();
    if (player.getCurrentHealth() <= 0) {
		player.setPosition(respawnPoint);
	  player.resetHealth();
    }
    return true;
  }
  return false;
}

std::vector<Enemy> getEnemies() { return vecEnemiesBuffer; }

void setEnemies(std::vector<Enemy> &newVector) {
	vecEnemiesBuffer = newVector;
}
