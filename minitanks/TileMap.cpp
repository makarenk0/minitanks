#include "TileMap.h"

TileMap::TileMap(std::string FILE, int tileSize, int width, int height, bool randomMap) {
  this->tileSize = tileSize;
  this->width = width;
  this->height = height;

  if (randomMap) {
	  generateMapRandom();
	  file = std::ifstream("maps/randomMap.txt");
  }
  else {
	  file = std::ifstream("maps/" + FILE);
  }

  tileTexture.loadFromFile("textures/exampleTileset.png");
  overlayTexture.loadFromFile("textures/destruct.png");

  solidBool = std::vector<std::vector<bool>>(height / tileSize,std::vector<bool>(width / tileSize, true)); // init vector with bools
  currentHealth = std::vector<std::vector<int>>(height / tileSize, std::vector<int>(width / tileSize, 0)); // init vector with currentHealth(by default health = 0)


  tiles.setPrimitiveType(sf::Quads);
  tiles.resize(width / tileSize * height / tileSize * 4); // init VertexArray with tiles vertices
  
 

  overlay.setPrimitiveType(sf::Quads);
  overlay.resize(width / tileSize * height / tileSize * 4); // init VertexArray with overlay vertices
  int counter = 0;
  while (true) {
    std::getline(file, buf);
    if (buf == "end")
      break;

    last = 1;
    buf = buf.substr(last);
    x = tileSize * std::stoi(readValue(buf)); // get x coord from file

    buf = buf.substr(last + 1);
    y = tileSize * std::stoi(readValue(buf)); // get y coord from file

    buf = buf.substr(last + 1);
    id = std::stoi(readValue(buf)); // get tile id from file(for texture)

    buf = buf.substr(last + 1);
    curHealth = std::stoi(readValue(buf));
    currentHealth[y / tileSize][x / tileSize] = curHealth; // get currentHealth, writing in vector

    buf = buf.substr(last + 1);
    if (std::stoi(readValue(buf)) == 1) {
      solid = true;
    } else {
      solid = false;
    }
    solidBool[y / tileSize][x / tileSize] = solid;

    sf::Vertex *quadTiles = &tiles[counter * 4];
    sf::Vertex *quadOverlay = &overlay[counter * 4];

	

    quadTiles[0].position = sf::Vector2f(x, y);
    quadTiles[1].position = sf::Vector2f(x + tileSize, y);
    quadTiles[2].position = sf::Vector2f(x + tileSize, y + tileSize);
    quadTiles[3].position = sf::Vector2f(x, y + tileSize);

    quadTiles[0].texCoords = sf::Vector2f(id * tileSize, 0);
    quadTiles[1].texCoords = sf::Vector2f(id * tileSize + tileSize, 0);
    quadTiles[2].texCoords = sf::Vector2f(id * tileSize + tileSize, tileSize);
    quadTiles[3].texCoords = sf::Vector2f(id * tileSize, tileSize);

    quadOverlay[0].position = sf::Vector2f(x, y);
    quadOverlay[1].position = sf::Vector2f(x + tileSize, y);
    quadOverlay[2].position = sf::Vector2f(x + tileSize, y + tileSize);
    quadOverlay[3].position = sf::Vector2f(x, y + tileSize);

    quadOverlay[0].texCoords = sf::Vector2f(curHealth * tileSize, 0);
    quadOverlay[1].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, 0);
    quadOverlay[2].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, tileSize);
    quadOverlay[3].texCoords = sf::Vector2f(curHealth * tileSize, tileSize);

	counter++;
  }
  file.close();
}
TileMap::~TileMap() {
  //	tiles.clear();
}
std::string TileMap::readValue(std::string str) {
  last = str.find(",");
  return (str.substr(0, str.find(",")));
}

bool TileMap::checkCollisionOfPoint(int xPoint, int yPoint) {
  xPoint = std::floor(xPoint / tileSize);
  yPoint = std::floor(yPoint / tileSize);
  if (solidBool[xPoint][yPoint]) {
    return true;
  }
  return false;
}


void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {   //override function of drawing
  target.draw(tiles, &tileTexture);
  target.draw(overlay, &overlayTexture);
}

void TileMap::changeCurrentHealth(int xPoint, int yPoint, int delta)
{
	
	xPoint = std::floor(xPoint / tileSize);
	yPoint = std::floor(yPoint / tileSize);
	curHealth = currentHealth[xPoint][yPoint] + delta;
	if (curHealth < 0) {
		curHealth = 0;
	}
	currentHealth[xPoint][yPoint] = curHealth;

	sf::Vertex* quadOverlay = &overlay[(xPoint+ yPoint * height / tileSize) * 4];
	quadOverlay[0].texCoords = sf::Vector2f(curHealth * tileSize, 0);
	quadOverlay[1].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, 0);
	quadOverlay[2].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, tileSize);
	quadOverlay[3].texCoords = sf::Vector2f(curHealth * tileSize, tileSize);

}

void TileMap::generateMapRandom(){
	std::ofstream randomMap("maps/randomMap.txt");
	for (int i = 0; i < (width / tileSize) * (height / tileSize); i++) {
		randomMap << "(" << i % (width / tileSize) <<","<< std::floor(i / (width/ tileSize))<<","<< rand()%3<<","<<rand()%5<<","<<rand()%2<<",)"<<std::endl;
	}
	randomMap << "end";
	randomMap.close();
}
