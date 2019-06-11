#include "TileMap.h"

TileMap::TileMap() { playersNum = 0; }
TileMap::TileMap(std::string FILE, int tileSize, int width, int height,
                 int widgetWidth, bool randomMap, bool editMode,
                 int playersNum) {

  initMap(FILE, tileSize, width, height, widgetWidth, randomMap, editMode,
          playersNum);
}

bool TileMap::initMap(std::string FILE, int tileSize, int width, int height,
                      int widgetWidth, bool randomMap, bool editMode,
                      int playersNum) {
  this->widgetWidth = widgetWidth;
  this->playersNum = playersNum;
  this->tileSize = tileSize;
  this->width = width;
  this->height = height;
  this->fileName = FILE;
  this->editMode = editMode;
  counterE = 0;
  toolsWidth = width;
  enemiesCords.clear();
  canvas.create(width, height);
  canvas.display();

  canvasOverlay.create(width, height);
  canvasOverlay.display();

  if (editMode) {
    exitEditMode = false;
    openEditWindow();
    generateMapEmpty();
    file = std::ifstream("maps/" + fileName + ".bcm");
    while (true) {
      if (buf == "end") {
        file.close();
        break;
      }
      std::getline(file, buf);
      fromFile.append(buf);
    }
  } else {
    if (randomMap) {
      generateMapRandom();
      file = std::ifstream("maps/" + fileName + ".txt");
      while (true) {
        if (buf == "end") {
          file.close();
          break;
        }
        std::getline(file, buf);
        fromFile += buf;
      }
    } else {
      fromFile = openFile();
      if (fromFile == "NULL") {
        return false;
      }
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

  // std::cout << fromFile.substr(0,fromFile.find(")"));
  while (true) {
    if (fromFile.substr(0, 3) == "end") {
      break;
    }
    buf = fromFile.substr(0, fromFile.find(")") + 1);

    fromFile = fromFile.substr(fromFile.find(")") + 1);
    last = 1;

    if (buf.substr(0, 2) == "p1") {
      buf = buf.substr(3);
      pl1X = tileSize * std::stoi(readValue(buf));
      buf = buf.substr(last + 1);
      pl1Y = tileSize * std::stoi(readValue(buf));
      continue;

    } else if (buf.substr(0, 2) == "p2") {
      buf = buf.substr(3);
      pl2X = tileSize * std::stoi(readValue(buf));
      buf = buf.substr(last + 1);
      pl2Y = tileSize * std::stoi(readValue(buf));
      continue;

    } else if (buf.substr(0, 9) == "allieBase") {
      buf = buf.substr(10);
      int xB = tileSize * std::stoi(readValue(buf));
      buf = buf.substr(last + 1);
      int yB = tileSize * std::stoi(readValue(buf));

      aliesB.loadFromFile("assets/mybase.png");
      allieBase.setTexture(aliesB);
      allieBase.setPosition(xB+widgetWidth, yB);
      allieBasePresent = true;
      continue;

    } else if (buf.substr(0, 9) == "enemyBase") {
      buf = buf.substr(10);
      int xB = tileSize * std::stoi(readValue(buf));
      buf = buf.substr(last + 1);
      int yB = tileSize * std::stoi(readValue(buf));
      enemyB.loadFromFile("assets/enemybase.png");
      enemyBase.setTexture(enemyB);
      enemyBase.setPosition(xB + widgetWidth, yB);
      enemyBasePresent = true;
      continue;

    } else if (buf.substr(0, 5) == "enemy") {
      enemiesCords.resize(counterE + 1);
      buf = buf.substr(6);
      int enemyX = tileSize * std::stoi(readValue(buf));
      buf = buf.substr(last + 1);
      int enemyY = tileSize * std::stoi(readValue(buf));
      enemiesCords[counterE].x = enemyX;
      enemiesCords[counterE].y = enemyY;

      counterE++;

      //std::cout << enemyX << "," << enemyY << std::endl;
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
  //  file.close();

  mainSprite.setPosition(widgetWidth, 0);
  mainSprite.setTexture(canvas.getTexture());

  overlaySprite.setPosition(widgetWidth, 0);
  overlaySprite.setTexture(canvasOverlay.getTexture());

  playersSprite.setPosition(widgetWidth, 0);
  playersSprite.setTexture(canvasPlayers.getTexture());

  canvas.draw(tiles, &tileTexture);
  canvasOverlay.draw(overlay, &overlayTexture);
  return true;
}

std::string TileMap::readValue(std::string str) {
  last = str.find(",");
  return (str.substr(0, str.find(",")));
}

bool TileMap::checkCollisionOfPoint(int xPoint, int yPoint) {

  xPoint = std::floor(xPoint / tileSize);
  yPoint = std::floor(yPoint / tileSize);

  if (bul && currentHealth[yPoint][xPoint] == 6) {
    return false;
  }

  if (solidBool[yPoint][xPoint]) {
    // std::cout << "true" << std::endl;
    return true;
  }
  // std::cout << "false" << std::endl;
  return false;
}

void TileMap::draw(sf::RenderWindow &window) { // override function of drawing
  if (firstLayer) {
    mainSprite.setTexture(canvas.getTexture());
    window.draw(mainSprite);
    if (allieBasePresent) {
      window.draw(allieBase);
    }
    if (enemyBasePresent) {
      window.draw(enemyBase);
    }

  } else {
    overlaySprite.setTexture(canvasOverlay.getTexture());
    window.draw(overlaySprite);
  }
  if (editMode) {
    window.draw(mapPl2);
    window.draw(mapPl1);
    window.draw(allieBase);
    window.draw(enemyBase);
    for (auto &i : enemiesEditMap) {
      window.draw(i);
    }
  }
}

void TileMap::setFirstLayer(bool set) { firstLayer = set; }

void TileMap::changeCurrentHealth(int xPoint, int yPoint, int delta) {

  xPoint = std::floor(xPoint / tileSize);
  yPoint = std::floor(yPoint / tileSize);
  curHealth = currentHealth[yPoint][xPoint] + delta;
  if (curHealth < 0) { // if the brick is destroyed, set the texture of ground
    curHealth = 4; // curHealth = 4 means that this tile could not be destroyed
                   //	currentHealth[yPoint][xPoint] = curHealth;
    sf::Vertex *quadTiles = &tiles[(xPoint + yPoint * width / tileSize) * 4];

    quadTiles[0].texCoords = sf::Vector2f(0, 0);
    quadTiles[1].texCoords = sf::Vector2f(tileSize, 0);
    quadTiles[2].texCoords = sf::Vector2f(tileSize, tileSize);
    quadTiles[3].texCoords = sf::Vector2f(0, tileSize);

    solidBool[yPoint][xPoint] =
        false; // set this tile available for player(not solid)
  }
  currentHealth[yPoint][xPoint] = curHealth;

  sf::Vertex *quadOverlay = &overlay[(xPoint + yPoint * width / tileSize) * 4];
  quadOverlay[0].texCoords = sf::Vector2f(curHealth * tileSize, 0);
  quadOverlay[1].texCoords = sf::Vector2f(curHealth * tileSize + tileSize, 0);
  quadOverlay[2].texCoords =
      sf::Vector2f(curHealth * tileSize + tileSize, tileSize);
  quadOverlay[3].texCoords = sf::Vector2f(curHealth * tileSize, tileSize);

  canvas.clear(sf::Color(255, 255, 255, 0)); // update
  canvas.draw(tiles, &tileTexture);
  canvasOverlay.clear(sf::Color(255, 255, 255, 0));
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
  std::ofstream customMap("maps/empty_map.bcm");
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
  counterE = 0;
  enemiesCords.resize(1);
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
        sf::Vector2f(indent + indent * (i + 5) + tileSize * (i + 5), indent);
    overlaysMenuPointer[1].position = sf::Vector2f(
        indent + indent * (i + 5) + tileSize * (i + 5) + tileSize, indent);
    overlaysMenuPointer[2].position =
        sf::Vector2f(indent + indent * (i + 5) + tileSize * (i + 5) + tileSize,
                     indent + tileSize);
    overlaysMenuPointer[3].position = sf::Vector2f(
        indent + indent * (i + 5) + tileSize * (i + 5), indent + tileSize);

    overlaysMenuPointer[0].texCoords = sf::Vector2f(i * tileSize, 0);
    overlaysMenuPointer[1].texCoords = sf::Vector2f(i * tileSize + tileSize, 0);
    overlaysMenuPointer[2].texCoords =
        sf::Vector2f(i * tileSize + tileSize, tileSize);
    overlaysMenuPointer[3].texCoords = sf::Vector2f(i * tileSize, tileSize);
  }

  pl1Text.loadFromFile("assets\\Player.png");
  pl1Edit.setTexture(pl1Text);
  pl1Edit.setScale(0.8, 0.8);
  pl1Edit.setPosition(toolsWidth - pl1Edit.getLocalBounds().width - indent,
                      indent);

  pl2Text.loadFromFile("assets\\Player2.png");
  pl2Edit.setTexture(pl2Text);
  pl2Edit.setScale(0.8, 0.8);
  pl2Edit.setPosition(
      toolsWidth - 2 * pl1Edit.getLocalBounds().width - (2 * indent), indent);

  allieBaseEditTex.loadFromFile("assets/mybase.png");
  allieBaseEdit.setTexture(allieBaseEditTex);
  allieBaseEdit.setPosition(toolsWidth - 2 * pl1Edit.getLocalBounds().width -
                                allieBaseEdit.getLocalBounds().width -
                                (3 * indent),
                            indent);

  enemyBaseEditTex.loadFromFile("assets/enemybase.png");
  enemyBaseEdit.setTexture(enemyBaseEditTex);
  enemyBaseEdit.setPosition(toolsWidth - 2 * pl1Edit.getLocalBounds().width -
                                2 * allieBaseEdit.getLocalBounds().width -
                                (4 * indent),
                            indent);

  enemy.loadFromFile("assets/enemy.png");
  enemySprite.setTexture(enemy);
  enemySprite.setPosition(toolsWidth - 3 * pl1Edit.getLocalBounds().width -
                              2 * allieBaseEdit.getLocalBounds().width -
                              (5 * indent),
                          indent);
}

bool TileMap::getEditMode() { return editMode; }

void TileMap::setEditMode(bool mode) { editMode = mode; }

void TileMap::editMap(sf::RenderWindow &mWindow) {

  drawToolWindow(mWindow.getPosition().x, mWindow.getPosition().y);

  if (exitEditMode) { // then goes code when user exit edit mode
    editMode = false;

    tools.close();
    toFile = "";
    int x;
    int y;
    for (int i = 0; i < (width / tileSize) * (height / tileSize); i++) {
      sf::Vertex *quadTiles = &tiles[i * 4];

      x = i % (width / tileSize);
      y = floor(i / (width / tileSize));
      toFile.append("(");
      toFile.append(std::to_string(x));
      toFile.append(",");
      toFile.append(std::to_string(y));
      toFile.append(",");
      toFile.append(std::to_string(int(quadTiles->texCoords.x / tileSize)));
      toFile.append(",");
      toFile.append(std::to_string(currentHealth[y][x]));
      toFile.append(",");
      toFile.append(std::to_string(solidBool[y][x]));
      toFile.append(",)\n");
    }

    toFile.append("p1(");
    toFile.append(std::to_string(
        int((mapPl1.getGlobalBounds().left - widgetWidth) / tileSize)));
    toFile.append(",");
    toFile.append(std::to_string(int(mapPl1.getGlobalBounds().top / tileSize)));
    toFile.append(",)\n");

    toFile.append("p2(");
    toFile.append(std::to_string(
        int((mapPl2.getGlobalBounds().left - widgetWidth) / tileSize)));
    toFile.append(",");
    toFile.append(std::to_string(int(mapPl2.getGlobalBounds().top / tileSize)));
    toFile.append(",)\n");

    for (int i = 0; i < counterE; i++) {
      toFile.append("enemy(");
      toFile.append(
          std::to_string(int((enemiesCords[i].x - widgetWidth) / tileSize)));
      toFile.append(",");
      toFile.append(std::to_string(int((enemiesCords[i].y) / tileSize)));
      toFile.append(",)\n");
    }
    toFile.append("p2(");
    toFile.append(std::to_string(
        int((mapPl2.getGlobalBounds().left - widgetWidth) / tileSize)));
    toFile.append(",");
    toFile.append(std::to_string(int(mapPl2.getGlobalBounds().top / tileSize)));
    toFile.append(",)\n");

    toFile.append("allieBase(");
    toFile.append(std::to_string(
        int((allieBase.getGlobalBounds().left - widgetWidth) / tileSize)));
    toFile.append(",");
    toFile.append(
        std::to_string(int(allieBase.getGlobalBounds().top / tileSize)));
    toFile.append(",)\n");

    toFile.append("enemyBase(");
    toFile.append(std::to_string(
        int((enemyBase.getGlobalBounds().left - widgetWidth) / tileSize)));
    toFile.append(",");
    toFile.append(
        std::to_string(int(enemyBase.getGlobalBounds().top / tileSize)));
    toFile.append(",)\n");

    toFile.append("end");
    saveFile(toFile);
  }

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if ((sf::Mouse::getPosition(mWindow).x - widgetWidth) / tileSize ==
        previousX) {
      if (sf::Mouse::getPosition(mWindow).y / tileSize == previousY) {
        return;
      }
    }
    previousX = (sf::Mouse::getPosition(mWindow).x - widgetWidth) / tileSize;
    previousY = sf::Mouse::getPosition(mWindow).y / tileSize;
    if (pl2EditPlaced) {
      if (previousY >= 0) {
        mapPl2.setTexture(pl2Text);
        mapPl2.setScale(0.8, 0.8);
        mapPl2.setPosition(previousX * tileSize + widgetWidth,
                           previousY * tileSize);
      }
    } else if (pl1EditPlaced) {
      if (previousY >= 0) {
        mapPl1.setTexture(pl1Text);
        mapPl1.setScale(0.8, 0.8);
        mapPl1.setPosition(previousX * tileSize + widgetWidth,
                           previousY * tileSize);
      }
    } else if (allieBasePlaced) {
      if (previousY >= 0) {
        allieBase.setTexture(allieBaseEditTex);
        allieBase.setPosition(previousX * tileSize + widgetWidth,
                              previousY * tileSize);
      }
    } else if (enemyBasePlaced) {
      if (previousY >= 0) {
        enemyBase.setTexture(enemyBaseEditTex);
        enemyBase.setPosition(previousX * tileSize + widgetWidth,
                              previousY * tileSize);
      }
    } else if (setEnemies) {
      if (previousY >= 0) {

        enemySprEdit.setTexture(enemy);
        enemySprEdit.setPosition(previousX * tileSize + widgetWidth,
                                 previousY * tileSize);
        enemiesEditMap.push_back(sf::Sprite(enemySprEdit));
        enemiesCords[counterE].x = previousX * tileSize + widgetWidth;
        enemiesCords[counterE].y = previousY * tileSize;
        counterE++;
        enemiesCords.resize(counterE + 1);
      }
    } else {
      if (previousX >= 0 && previousX < width / tileSize && previousY >= 0 &&
          previousY < height / tileSize) {
        changeTile(previousX, previousY);
      }
    }

    return;
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
  //std::cout << healthEdit << std::endl;
  quadOverlay[0].texCoords = sf::Vector2f(healthEdit * tileSize, 0);
  quadOverlay[1].texCoords = sf::Vector2f(healthEdit * tileSize + tileSize, 0);
  quadOverlay[2].texCoords =
      sf::Vector2f(healthEdit * tileSize + tileSize, tileSize);
  quadOverlay[3].texCoords = sf::Vector2f(healthEdit * tileSize, tileSize);

  currentHealth[Y][X] = healthEdit;
  solidBool[Y][X] = solEdit;

  canvas.clear(sf::Color(255, 255, 255, 0)); // update
  canvas.draw(tiles, &tileTexture);
  canvasOverlay.clear(sf::Color(255, 255, 255, 0));
  canvasOverlay.draw(overlay, &overlayTexture);
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
  tools.setPosition(sf::Vector2i(winX + widgetWidth, winY - toolsHeight - 43));
  // tool menu
  tools.draw(toolsMenu, &tileTexture);
  tools.draw(overlaysMenu, &overlayTexture);
  if (!pl1EditPlaced) {
    tools.draw(pl1Edit);
  }
  if (!pl2EditPlaced) {
    tools.draw(pl2Edit);
  }
  if (!allieBasePlaced) {
    tools.draw(allieBaseEdit);
  }
  if (!enemyBasePlaced) {
    tools.draw(enemyBaseEdit);
  }
  tools.draw(enemySprite);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    int x = sf::Mouse::getPosition(tools).x;
    int y = sf::Mouse::getPosition(tools).y;

    // clicks
    if (x >= toolsMenu[3].position.x && x <= toolsMenu[1].position.x) {
      if (y >= toolsMenu[1].position.y && y <= toolsMenu[3].position.y) {
        idEdit = 0;
        healthEdit = 4;
        solEdit = false;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }
    if (x >= toolsMenu[3 + 4].position.x && x <= toolsMenu[1 + 4].position.x) {
      if (y >= toolsMenu[1 + 4].position.y &&
          y <= toolsMenu[3 + 4].position.y) {
        idEdit = 1;
        healthEdit = 3;
        solEdit = true;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }
    if (x >= toolsMenu[3 + 8].position.x && x <= toolsMenu[1 + 8].position.x) {
      if (y >= toolsMenu[1 + 8].position.y &&
          y <= toolsMenu[3 + 8].position.y) {
        idEdit = 2;
        healthEdit = 4;
        solEdit = true;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }
    if (x >= toolsMenu[3 + 12].position.x &&
        x <= toolsMenu[1 + 12].position.x) {
      if (y >= toolsMenu[1 + 12].position.y &&
          y <= toolsMenu[3 + 12].position.y) {
        idEdit = 0;
        healthEdit = 5;
        solEdit = false;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }

    if (x >= toolsMenu[3 + 16].position.x &&
        x <= toolsMenu[1 + 16].position.x) {
      if (y >= toolsMenu[1 + 16].position.y &&
          y <= toolsMenu[3 + 16].position.y) {
        idEdit = 4;
        healthEdit = 6;
        solEdit = true;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }

    if (x >= overlaysMenu[3].position.x && x <= overlaysMenu[1].position.x) {
      if (y >= overlaysMenu[1].position.y && y <= overlaysMenu[3].position.y) {
        idEdit = 1;
        healthEdit = 0;
        solEdit = true;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }
    if (x >= overlaysMenu[3 + 4].position.x &&
        x <= overlaysMenu[1 + 4].position.x) {
      if (y >= overlaysMenu[1 + 4].position.y &&
          y <= overlaysMenu[3 + 4].position.y) {
        idEdit = 1;
        healthEdit = 1;
        solEdit = true;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }
    if (x >= overlaysMenu[3 + 8].position.x &&
        x <= overlaysMenu[1 + 8].position.x) {
      if (y >= overlaysMenu[1 + 8].position.y &&
          y <= overlaysMenu[3 + 8].position.y) {
        idEdit = 1;
        healthEdit = 2;
        solEdit = true;

        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }

    if (x >= pl2Edit.getPosition().x &&
        x <= pl2Edit.getPosition().x + pl2Edit.getLocalBounds().width) {
      if (y >= pl2Edit.getPosition().y &&
          y <= pl2Edit.getPosition().y + pl2Edit.getLocalBounds().height) {
        pl2EditPlaced = true;
        pl1EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }

    if (x >= pl1Edit.getPosition().x &&
        x <= pl1Edit.getPosition().x + pl1Edit.getLocalBounds().width) {
      if (y >= pl1Edit.getPosition().y &&
          y <= pl1Edit.getPosition().y + pl1Edit.getLocalBounds().height) {
        pl1EditPlaced = true;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }

    if (x >= allieBaseEdit.getPosition().x &&
        x <= allieBaseEdit.getPosition().x +
                 allieBaseEdit.getLocalBounds().width) {
      if (y >= allieBaseEdit.getPosition().y &&
          y <= allieBaseEdit.getPosition().y +
                   allieBaseEdit.getLocalBounds().height) {
        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = true;
        setEnemies = false;
      }
    }

    if (x >= enemyBaseEdit.getPosition().x &&
        x <= enemyBaseEdit.getPosition().x +
                 enemyBaseEdit.getLocalBounds().width) {
      if (y >= enemyBaseEdit.getPosition().y &&
          y <= enemyBaseEdit.getPosition().y +
                   enemyBaseEdit.getLocalBounds().height) {
        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = true;
        allieBasePlaced = false;
        setEnemies = false;
      }
    }

    if (x >= enemySprite.getPosition().x &&
        x <= enemySprite.getPosition().x + enemySprite.getLocalBounds().width) {
      if (y >= enemySprite.getPosition().y &&
          y <= enemySprite.getPosition().y +
                   enemySprite.getLocalBounds().height) {
        pl1EditPlaced = false;
        pl2EditPlaced = false;
        enemyBasePlaced = false;
        allieBasePlaced = false;
        setEnemies = true;
      }
    }
  }

  tools.display();
}

bool TileMap::checkTile(sf::FloatRect bullet,bool real) {
	if (real) {
		if (bullet.top < 5 || bullet.top + 26 > height ||
			bullet.left - widgetWidth < 5 ||
			bullet.left - widgetWidth + 26 > width-5) {
			if (bullet.top < 0 || bullet.top > height ||
				bullet.left - widgetWidth < 0 || bullet.left - widgetWidth > width-5) {

				return true;
			}
		}
		else {
			// std::cout << enemyBase.getGlobalBounds().left <<","<<
			// enemyBase.getGlobalBounds().top << std::endl;
			for (int i = (int(bullet.top)) / tileSize;
				i <= ((int(bullet.top) + int(bullet.height)) / tileSize); i++) {
				for (int j = (int(bullet.left - widgetWidth)) / tileSize;
					j <=
					((int(bullet.left - widgetWidth) + int(bullet.width)) / tileSize);
					j++) {

					if ((j * tileSize ==
						int(enemyBase.getGlobalBounds().left - widgetWidth)) &&
						(i * tileSize == int(enemyBase.getGlobalBounds().top))) {
						win = true;
					}
					else if (j * tileSize ==
						int(allieBase.getGlobalBounds().left - widgetWidth) &&
						i * tileSize == int(allieBase.getGlobalBounds().top)) {
						fail = true;
					}
					bul = true;
					if (this->checkCollisionOfPoint(j * tileSize, i * tileSize)) {

						if (currentHealth[i][j] < 4) {
							this->changeCurrentHealth(j * tileSize, i * tileSize, -1);
						}
						return true;
					}
					bul = false;
				}
			}
		}
	}
  return false;
}

std::vector<sf::Vector2f> &TileMap::getEnemiesCords() { return enemiesCords; }
