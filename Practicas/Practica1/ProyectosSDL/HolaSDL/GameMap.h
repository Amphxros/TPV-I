#pragma once
#include <string>

#include "Vector2D.h"
#include "Texture.h"
using namespace std;

enum MapCell {Empty, Wall, Food, Vitamins};	//Solo contiene info de elementos estáticos

class Game;
class GameMap
{
public:
	GameMap(int rows, int cols, Texture* texture,Game* game);
	
	~GameMap();

	void write(int x, int y, MapCell m);
	void render();

	//devuelve una pos i,j
	MapCell getCell(int i, int j) { return map[i][j]; }
	//devuelve si la pos i,j es un muro
	bool isCellWall(int i, int j) { return map[i][j]==MapCell::Wall; }
	//devuelve si la pos i,j es comida
	bool isCellFood(int i, int j) { return map[i][j]==MapCell::Food; }
	//devuelve si la pos i,j es vitamina
	bool isCellVitamin(int i, int j) { return map[i][j]==MapCell::Vitamins; }

	void setMapCellEmpty(MapCell m) { m = MapCell::Empty; }
	void setMapCellEmpty(int i, int j) { map[i][j] = MapCell::Empty; }
private:

	Vector2D mapSize;
	MapCell** map; //Array de celdas de tipo MapCell; Contienen info de lo que hay en las casillas
	Game* game_;
	Texture* texture_;
	int rows_, cols_;
};

