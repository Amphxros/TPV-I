#pragma once
#include "Vector2D.h"
#include "Texture.h"

#include "checkML.h"

class Game;

class Ghost
{
public:
	//constructor
	Ghost(Point2D pos, Texture* Texture, Game* game,int color);
	//destructor
	~Ghost();

	//render
	void render();
	//update
	void update();

	//devuelve la posicion
	Vector2D getPos() { return pos_; };	// Posición a la que quiere avanzar
	//cambia la posicion
	void setPos(Vector2D pos) { pos_ = pos; };
private:
	Point2D pos_; //posicion
	Vector2D dir_;	//Direccion a la que quiere avanzar
	Texture* texture_; //textura
	Game* game_; //puntero a juego
	int color_; //color del fantasma
};

