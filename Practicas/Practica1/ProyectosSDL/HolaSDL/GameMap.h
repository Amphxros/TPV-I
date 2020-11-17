#pragma once
#include <string>

#include "Vector2D.h"
#include "Texture.h"

#include "checkML.h"
using namespace std;

enum MapCell {Empty, Wall, Food, Vitamins};	//Solo contiene info de elementos estáticos

class Game;
class GameMap
{
public:
	//constructora
	GameMap(int rows, int cols, Texture* texture,Game* game);
	//destructora
	~GameMap();

	// Rellena la casilla x, y con el tipo m, se usa en la creadora
	void write(int x, int y, MapCell m) { map[x][y] = m; };
	//renderiza la matriz map
	void render();	

	// Devuelve lo que hay en una pos i,j
	MapCell getCell(int i, int j) { return map[i][j]; };

	// Devuelve si la pos i,j es un muro, comida o vitamina
	bool isCellWall(int i, int j) { return map[i][j] == MapCell::Wall; };
	bool isCellFood(int i, int j) { return map[i][j] == MapCell::Food; };
	bool isCellVitamin(int i, int j) { return map[i][j] == MapCell::Vitamins; };

private:

	MapCell** map; //Array de celdas de tipo MapCell; Contienen info de lo que hay en las casillas
	Game* game_; //puntero a game
	Texture* texture_; //textura del mapa (spritesheet de tiles)
	int rows_, cols_; //numero de filas y columnas
};

