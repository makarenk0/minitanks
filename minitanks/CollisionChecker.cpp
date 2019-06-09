#include "CollisionChecker.h"
void checkCollisionTiles(TileMap &map, std::vector<Bullet> &vecBullets) {
  for (auto &i : vecBullets) {
    // bool hit = map.checkTile(i.getGlobalBounds());
    //	if (hit) i.~Bullet();
  }
}

std::vector<Bullet> vec;

std::vector<Entity> checkCollisionEntities(std::vector<Bullet> &vecBullets,
                                           std::vector<Entity> &vecEnt,
                                           sf::Sound &hit) {
  int indexI = 0;
  int indexK = 0;
  for (auto &k : vecEnt) {

    for (auto &i : vecBullets) {

      if (i.getGlobalBounds().intersects(k.getGlobalBounds())) {
        i.~Bullet();
        hit.play();
        vecBullets[indexI] = vecBullets.back();
        vecBullets.pop_back();

        k.setCurrentHealth(k.getCurrentHealth() - 1);
        if (k.getCurrentHealth() <= 0) {
          k.~Entity();
          std::vector<Entity>::iterator it2 = vecEnt.begin() + indexK;
          vecEnt.erase(it2);
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

std::vector<Bullet> getVector() { return vec; }
