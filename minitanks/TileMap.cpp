#include "TileMap.h"



TileMap::TileMap(std::string FILE, int tileSize, int width, int height){
	file = std::ifstream("maps/"+FILE);
	tileTexture.loadFromFile("textures/tileset.png");

	tiles.setPrimitiveType(sf::Quads);
	tiles.resize(width/tileSize * height/tileSize * 4); //init vector with vertices

	while (true) {
		std::getline(file, buf);
		if (buf == "end") break;

		last = 1;
		buf = buf.substr(last);
		x =tileSize*readValue(buf);   //get x coord from file

		buf = buf.substr(last+1);
		y = tileSize*readValue(buf);   //get y coord from file
	

		buf = buf.substr(last + 1);
		id = readValue(buf);   //get tile id from file(for texture)

		buf = buf.substr(last + 1);  
		if (readValue(buf) == 1) {
			solid = true;
		}
		else {
			solid = false;
		}

		if (x+tileSize == width) {
			solidBool.push_back(buffer);
			buffer.clear();
		}
		else {
			buffer.push_back(solid);
		}

		sf::Vertex* quad = &tiles[(x/tileSize+y/tileSize*height/tileSize)*4];

		quad[0].position = sf::Vector2f(x, y);
		quad[1].position = sf::Vector2f(x+tileSize, y);
		quad[2].position = sf::Vector2f(x + tileSize, y + tileSize);
		quad[3].position = sf::Vector2f(x, y + tileSize);


	

		quad[0].texCoords = sf::Vector2f(id * tileSize, 0);
		quad[1].texCoords = sf::Vector2f(id * tileSize+ tileSize, 0 );
		quad[2].texCoords = sf::Vector2f(id * tileSize + tileSize, tileSize);
		quad[3].texCoords = sf::Vector2f(id * tileSize, tileSize);

//		quad[0].color = sf::Color::Red;  //color for tests
//		quad[1].color = sf::Color::Red;
//		quad[2].color = sf::Color::Red;
//		quad[3].color = sf::Color::Red;


		
	}

}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &tileTexture;
	target.draw(tiles, states);
}



int TileMap::readValue(std::string str)
{
	last = str.find(",");
	return std::stoi(str.substr(0, str.find(",")));
}


