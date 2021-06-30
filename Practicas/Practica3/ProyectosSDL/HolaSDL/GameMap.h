#pragma once
#include <string>
#include "checkML.h"

#include "GameObject.h"

using namespace std;

enum class MapCell {Empty, Wall, Food, Vitamins};	//Solo contiene info de elementos estáticos

class PlayState;
class GameMap	:	public GameObject
{
public:

	GameMap() : GameObject() { throw "Mapa nulo"; }
	GameMap(Point2D pos, double width, double height, int rows, int cols, Texture* texture,GameState* game);
	virtual ~GameMap();

	void render();	
	void update(){}

	// Rellena la casilla x, y con el tipo m, se usa en la lectura
	void write(int x, int y, MapCell m) { map[x][y] = m; };

	bool IntersectWall(SDL_Rect dest); //comprueba si dest coincide con un muro
	bool IntersectFood(SDL_Rect dest); //comprueba si dest coincide con comida y la sobreescribe

	// Devuelve lo que hay en una pos i,j
	MapCell getCell(int i, int j) { return map[i][j]; };

	// Devuelve si la pos i,j es un muro, comida o vitamina
	bool isCellWall(int i, int j) { return map[i][j] == MapCell::Wall; };
	bool isCellFood(int i, int j) { return map[i][j] == MapCell::Food; };
	bool isCellVitamin(int i, int j) { return map[i][j] == MapCell::Vitamins; };

private:

	MapCell** map; //Array de celdas de tipo MapCell; Contienen info de lo que hay en las casillas
	int rows_, cols_; //numero de filas y columnas
	PlayState* game_state;

};