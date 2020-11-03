#pragma once
#include <string>

#include "Vector2D.h"
using namespace std;

class GameMap
{
public:
	GameMap(std::string filename) { leeArchivo(filename); };
	~GameMap() { delete map; map = nullptr; };

	void leeArchivo(std::string filename);
	void escribeArchivo(std::string filename);

	

private:

	enum MapCell {Empty, Wall, Food, Vitamins};	//Solo contiene info de elementos estáticos
	Vector2D mapSize;
	MapCell** map; //Array de celdas de tipo MapCell; Contienen info de lo que hay en las casillas

};

