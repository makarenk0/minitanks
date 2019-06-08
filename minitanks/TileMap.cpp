#include "TileMap.h"

TileMap::TileMap(std::string FILE, int tileSize, int width, int height, int widgetWidth,
                 bool randomMap, bool editMode, int playersNum) {
	this->widgetWidth = widgetWidth;
	this->playersNum = playersNum;
  initMap(FILE, tileSize, width, height, randomMap, editMode);
}

void TileMap::initMap(std::string FILE, int tileSize, int width, int height,
                      bool randomMap, bool editMode) {
  this->tileSize = tileSize;
  this->width = width;
  this->height = height;
  this->fileName = FILE;
  this->editMode = editMode;

  toolsWidth = width;

  canvas.create(width, height);
  canvas.display();

  canvasOverlay.create(width, height);
  canvasOverlay.display();

  if (editMode) {
    exitEditMode = false;
    openEditWindow();
    generateMapEmpty();
    file = std::ifstream("maps/" + fileName + ".txt");

  } else {
    if (randomMap) {
      generateMapRandom();
      file = std::ifstream("maps/" + fileName + ".txt");
    } else {
      file = std::ifstream("maps/" + fileName + ".txt");
    }
  }

  tileTexture.loadFromFile("assets\\tiles.png");
  overlayTexture.loadFromFile("assets\\overlays.png");

  solidBool = std::vector<std::vector<bool>>(
      height / tileSize,
      std::vector<bool>(width / tileSize, true)); // init vector with bools
  currentHealth = std::vector<std::vector<int>>(
      height / tileSize,
      std::vector<int>(
          width / tileSize,
          0)); // init vector with currentHealth(by default health = 0)

  tiles.setPrimitiveType(sf::Quads);
  tiles.resize(width / tileSize * height / tileSize *
               4); // init VertexArray with tiles vertices

  overlay.setPrimitiveType(sf::Quads);
  overlay.resize(width / tileSize * height / tileSize *
                 4); // init VertexArray with overlay vertices

  int counter = 0;
  while (true) {
    std::getline(file, buf);
	last = 1;

	if (buf.substr(0, 2) == "p1") {
		buf = buf.substr(3);
		pl1X = tileSize * std::stoi(readValue(buf));
		buf = buf.substr(last + 1);
		pl1Y = tileSize * std::stoi(readValue(buf));
		std::cout << pl1X << "," << pl1Y;
		continue;

	}
	else if (buf.substr(0, 2) == "p2") {
		buf = buf.substr(3);
		pl2X = tileSize * std::stoi(readValue(buf));
		buf = buf.substr(last + 1);
		pl2Y = tileSize * std::stoi(readValue(buf));
		std::cout << pl1X << "," << pl1Y;
		continue;

	}
    if (buf == "end")
      break;

    
    buf = buf.substr(last);
    x = tileSize * std::stoi(readValue(buf)); // get x coord from file

    buf = buf.substr(last + 1);
    y = tileSize * std::stoi(readValue(buf)); // get y coord from file

    buf = buf.substr(last + 1);
    id = std::stoi(readValue(buf)); // get tile id from file(for texture)

    buf = buf.substr(last + 1);
    curHealth = std::stoi(readValue(buf));
    currentHealth[y / tileSize][x / tileSize] =
        curHealth; // get currentHealth, writing in vector

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

    quadOverlay[0].position = sf::Vector2f(x, y);
    quadOverlay[1].position = sf::Vector2f(x + tileSize, y);
    quadOverlay[2].position = sf::Vector2f(x + tileSize, y + tileSize);
    quadOverlay[3].position = sf::Vector2f(x, y + tileSize);

    if (id == 3) { // cells with id=3 are cells with bushes overlays
      id = 0;
      curHealth = 5;
    }

    quadTiles[0].texCoords = sf::Vector2f(id * tileSize, 0);
    quadTiles[1].texCoords = sf::Vector2f(id * tileSize + tileSize, 0);
    quadTiles[2].texCoords = sf::Vector2f(id * tileSize + tileSize, tileSize);
    quadTiles[3].texCoords = sf::Vector2f(id * tileSize, tileSize);

    quadOverlay[0].texCoords = sf::Vector2f(curHealth * tileSize, 0);
    quadOverlay[1].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, 0);
    quadOverlay[2].texCoords =
        sf::Vector2f(curHealth * tileSize + tileSize, tileSize);
    quadOverlay[3].texCoords = sf::Vector2f(curHealth * tileSize, tileSize);

    counter++;
  }
  file.close();

  mainSprite.setPosition(widgetWidth, 0);
  mainSprite.setTexture(canvas.getTexture());

  overlaySprite.setPosition(widgetWidth, 0);
  overlaySprite.setTexture(canvasOverlay.getTexture());

  canvas.draw(tiles, &tileTexture);
  canvasOverlay.draw(overlay, &overlayTexture);
  
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
  if (solidBool[yPoint][xPoint]) {
    // std::cout << "true" << std::endl;
    return true;
  }
  // std::cout << "false" << std::endl;
  return false;
}

void TileMap::draw(sf::RenderWindow &window){ // override function of drawing
	if (firstLayer) {
		window.draw(mainSprite);
    }
	else {
		window.draw(overlaySprite);
	}
  
}

void TileMap::setFirstLayer(bool set) {
	firstLayer = set;
}





void TileMap::changeCurrentHealth(int xPoint, int yPoint, int delta) {

  xPoint = std::floor(xPoint / tileSize);
  yPoint = std::floor(yPoint / tileSize);
  curHealth = currentHealth[xPoint][yPoint] + delta;
  if (curHealth < 0) { // if the brick is destroyed, set the texture of ground
    curHealth = 4; // curHealth = 4 means that this tile could not be destroyed
    currentHealth[xPoint][yPoint] = curHealth;
    sf::Vertex *quadTiles = &tiles[xPoint * yPoint * 4];

    quadTiles[0].texCoords = sf::Vector2f(0, 0);
    quadTiles[1].texCoords = sf::Vector2f(tileSize, 0);
    quadTiles[2].texCoords = sf::Vector2f(tileSize, tileSize);
    quadTiles[3].texCoords = sf::Vector2f(0, tileSize);

    solidBool[yPoint][xPoint] =
        false; // set this tile available for player(not solid)
    return;
  }
  currentHealth[xPoint][yPoint] = curHealth;

  sf::Vertex *quadOverlay = &overlay[(xPoint + yPoint * height / tileSize) * 4];
  quadOverlay[0].texCoords = sf::Vector2f(curHealth * tileSize, 0);
  quadOverlay[1].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, 0);
  quadOverlay[2].texCoords =
      sf::Vector2f(curHealth * tileSize + tileSize, tileSize);
  quadOverlay[3].texCoords = sf::Vector2f(curHealth * tileSize, tileSize);

  canvas.draw(tiles, &tileTexture);    //update
  canvasOverlay.draw(overlay, &overlayTexture);
}

void TileMap::generateMapRandom() {
  std::ofstream randomMap("maps/" + fileName + ".txt");
  int tileId;
  int health;
  bool sol;
  srand(time(0));
  for (int i = 0; i < (width / tileSize) * (height / tileSize); i++) {
    tileId = rand() % 3;
    health = rand() % 4;
    if (tileId == 0) { // this means that if this tile isnt a brick, it couldnt
                       // have different health
      if (tileId == 0 && health < 2) {
        health = 5; // set an overlay bush
        sol = false;
      } else {
        health = 4;
        sol = false;
      }
    } else if (tileId == 1) {
      sol = true;
    } else {
      sol = true;
      health = 4;
    }
    randomMap << "(" << i % (width / tileSize) << ","
              << std::floor(i / (width / tileSize)) << "," << tileId << ","
              << health << "," << sol << ",)" << std::endl;
  }
  randomMap << "end";
  randomMap.close();
}

void TileMap::generateMapEmpty() {
  std::ofstream customMap("maps/" + fileName + ".txt");
  for (int i = 0; i < (width / tileSize) * (height / tileSize); i++) {
    customMap << "(" << i % (width / tileSize) << ","
              << std::floor(i / (width / tileSize)) << "," << 0 << "," << 4
              << "," << false << ",)" << std::endl;
  }
  customMap << "end";
  customMap.close();
}

void TileMap::openEditWindow() {
  tools.create(sf::VideoMode(toolsWidth, toolsHeight), "tools",
               sf::Style::Titlebar);
  // init graphic part of menu
  toolsMenu.resize(amountOfTools * 4);
  overlaysMenu.resize(amountOfTools * 4);

  toolsMenu.setPrimitiveType(sf::Quads);
  overlaysMenu.setPrimitiveType(sf::Quads);
  int indent = 20; // 20 px between buttons
  for (int i = 0; i < amountOfTools; i++) {
    sf::Vertex *toolsPointer = &toolsMenu[i * 4];
    toolsPointer[0].position =
        sf::Vector2f(indent + indent * i + tileSize * i, indent);
    toolsPointer[1].position =
        sf::Vector2f(indent + indent * i + tileSize * i + tileSize, indent);
    toolsPointer[2].position = sf::Vector2f(
        indent + indent * i + tileSize * i + tileSize, indent + tileSize);
    toolsPointer[3].position =
        sf::Vector2f(indent + indent * i + tileSize * i, indent + tileSize);

    toolsPointer[0].texCoords = sf::Vector2f(i * tileSize, 0);
    toolsPointer[1].texCoords = sf::Vector2f(i * tileSize + tileSize, 0);
    toolsPointer[2].texCoords = sf::Vector2f(i * tileSize + tileSize, tileSize);
    toolsPointer[3].texCoords = sf::Vector2f(i * tileSize, tileSize);
  }
  for (int i = 0; i < 3; i++) { // buttons for bricks health
    sf::Vertex *overlaysMenuPointer = &overlaysMenu[i * 4];
    overlaysMenuPointer[0].position =
        sf::Vector2f(indent + indent * (i+4) + tileSize * (i+4), indent);
    overlaysMenuPointer[1].position = sf::Vector2f(
		indent + indent * (i+4) + tileSize * (i+4) + tileSize, indent);
    overlaysMenuPointer[2].position =
        sf::Vector2f(indent + indent * (i+4) + tileSize * (i+4) + tileSize, indent + tileSize);
    overlaysMenuPointer[3].position = sf::Vector2f(
		indent + indent * (i+4) + tileSize * (i+4), indent + tileSize);

    overlaysMenuPointer[0].texCoords = sf::Vector2f(i * tileSize, 0);
    overlaysMenuPointer[1].texCoords = sf::Vector2f(i * tileSize + tileSize, 0);
    overlaysMenuPointer[2].texCoords =
        sf::Vector2f(i * tileSize + tileSize, tileSize);
    overlaysMenuPointer[3].texCoords = sf::Vector2f(i * tileSize, tileSize);
  }
}

bool TileMap::getEditMode() { return editMode; }

void TileMap::setEditMode(bool mode) { editMode = mode; }

void TileMap::editMap(sf::RenderWindow &mWindow) {
	canvas.draw(tiles, &tileTexture);    //update
	canvasOverlay.draw(overlay, &overlayTexture);

  drawToolWindow(mWindow.getPosition().x, mWindow.getPosition().y);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if ((sf::Mouse::getPosition(mWindow).x-widgetWidth) / tileSize == previousX) {
      if (sf::Mouse::getPosition(mWindow).y / tileSize == previousY) {
        return;
      }
    }
    previousX = (sf::Mouse::getPosition(mWindow).x-widgetWidth) / tileSize;
    previousY = sf::Mouse::getPosition(mWindow).y / tileSize;

    if (previousX >= 0 && previousX < width / tileSize && previousY >= 0 &&
        previousY < height / tileSize) {
      changeTile(previousX, previousY);
    }
    return;
  }
  // then goes code when user exit edit mode
  if (exitEditMode) {
    editMode = false;
    tools.close();

    std::ofstream customMap("maps/" + fileName + ".txt");
    for (int i = 0; i < (width / tileSize) * (height / tileSize); i++) {
      sf::Vertex *quadTiles = &tiles[i * 4];

      int x = i % (width / tileSize);
      int y = floor(i / (width / tileSize));
      customMap << "(" << i % (width / tileSize) << ","
                << std::floor(i / (width / tileSize)) << ","
                << quadTiles->texCoords.x / tileSize << ","
                << currentHealth[y][x] << "," << solidBool[y][x] << ",)"
                << std::endl;
    }
    customMap << "end";
    customMap.close();
  }
}

void TileMap::setExitEditMode(bool ex) { exitEditMode = ex; }

void TileMap::changeTile(int X, int Y) {
  sf::Vertex *quadTiles = &tiles[(width / tileSize * Y + X) * 4];
  sf::Vertex *quadOverlay = &overlay[(width / tileSize * Y + X) * 4];

  quadTiles[0].texCoords = sf::Vector2f(idEdit * tileSize, 0);
  quadTiles[1].texCoords = sf::Vector2f(idEdit * tileSize + tileSize, 0);
  quadTiles[2].texCoords = sf::Vector2f(idEdit * tileSize + tileSize, tileSize);
  quadTiles[3].texCoords = sf::Vector2f(idEdit * tileSize, tileSize);

  quadOverlay[0].texCoords = sf::Vector2f(healthEdit * tileSize, 0);
  quadOverlay[1].texCoords = sf::Vector2f(healthEdit * tileSize + tileSize, 0);
  quadOverlay[2].texCoords =
      sf::Vector2f(healthEdit * tileSize + tileSize, tileSize);
  quadOverlay[3].texCoords = sf::Vector2f(healthEdit * tileSize, tileSize);

  currentHealth[Y][X] = healthEdit;
  solidBool[Y][X] = solEdit;
}

void TileMap::drawToolWindow(int winX, int winY) {
  sf::Event event;
  while (tools.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed: {
      tools.close();
      break;
    }
    }
  }
  tools.clear(sf::Color(173, 216, 230));
  tools.setPosition(sf::Vector2i(winX + widgetWidth, winY-toolsHeight-43));
  // tool menu
  tools.draw(toolsMenu, &tileTexture);
  tools.draw(overlaysMenu, &overlayTexture);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    int x = sf::Mouse::getPosition(tools).x;
    int y = sf::Mouse::getPosition(tools).y;
    if (x >= toolsMenu[3].position.x && x <= toolsMenu[1].position.x) {
      if (y >= toolsMenu[1].position.y && y <= toolsMenu[3].position.y) {
        idEdit = 0;
        healthEdit = 4;
        solEdit = false;
      }
    }
    if (x >= toolsMenu[3 + 4].position.x && x <= toolsMenu[1 + 4].position.x) {
      if (y >= toolsMenu[1 + 4].position.y &&
          y <= toolsMenu[3 + 4].position.y) {
        idEdit = 1;
        healthEdit = 4;
        solEdit = true;
      }
    }
    if (x >= toolsMenu[3 + 8].position.x && x <= toolsMenu[1 + 8].position.x) {
      if (y >= toolsMenu[1 + 8].position.y &&
          y <= toolsMenu[3 + 8].position.y) {
        idEdit = 2;
        healthEdit = 4;
        solEdit = true;
      }
    }
    if (x >= toolsMenu[3 + 12].position.x &&
        x <= toolsMenu[1 + 12].position.x) {
      if (y >= toolsMenu[1 + 12].position.y &&
          y <= toolsMenu[3 + 12].position.y) {
        idEdit = 0;
        healthEdit = 5;
        solEdit = false;
      }
    }

    if (x >= overlaysMenu[3].position.x && x <= overlaysMenu[1].position.x) {
      if (y >= overlaysMenu[1].position.y && y <= overlaysMenu[3].position.y) {
        idEdit = 1;
        healthEdit = 0;
        solEdit = true;
      }
    }
    if (x >= overlaysMenu[3 + 4].position.x &&
        x <= overlaysMenu[1 + 4].position.x) {
      if (y >= overlaysMenu[1 + 4].position.y &&
          y <= overlaysMenu[3 + 4].position.y) {
        idEdit = 1;
        healthEdit = 1;
        solEdit = true;
      }
    }
    if (x >= overlaysMenu[3 + 8].position.x &&
        x <= overlaysMenu[1 + 8].position.x) {
      if (y >= overlaysMenu[1 + 8].position.y &&
          y <= overlaysMenu[3 + 8].position.y) {
        idEdit = 1;
        healthEdit = 2;
        solEdit = true;
      }
    }
  }

  tools.display();
}
