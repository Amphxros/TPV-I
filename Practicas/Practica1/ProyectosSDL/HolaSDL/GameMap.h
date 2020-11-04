#pragma once
#include <string>

#include "Vector2D.h"
#include "Texture.h"
using namespace std;

class GameMap
{
public:
	GameMap(std::string filename) { load(filename); };
	GameMap(int rows, int cols, std::string filename, Texture* tex0, Texture* tex1, Texture* tex2, Texture* tex3);
	
	~GameMap() { delete map; map = nullptr; };

	void load(std::string filename);
	void write(std::string filename);

	

private:

	enum MapCell {Empty, Wall, Food, Vitamins};	//Solo contiene info de elementos estáticos
	Vector2D mapSize;
	MapCell** map; //Array de celdas de tipo MapCell; Contienen info de lo que hay en las casillas

};

