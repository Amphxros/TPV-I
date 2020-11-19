#pragma once
#include "Vector2D.h"
#include "Texture.h"

#include "checkML.h"

class Game;

class Pacman
{
public:
	
	Pacman(Point2D pos, Texture* texture, Game* game_, int numVidas);
	~Pacman();

	void render();
	void update();
	void handleEvents(SDL_Event& event);

	void setNyom(bool comer);	// Come la vitamina y activa la debilidad en los fantasmas
	bool getNyom() { return nyom; };
	
	void setVidas(int v) { vidas = v; }
	int getVidas() { return vidas; };

	Vector2D getPos() { return pos_ + dir_; };	// Devuelve la posicion a la que intenta moverse
	Vector2D getCurrPos() { return pos_; };	// Devuelve la posicion a la que intenta moverse
	
	void setPos(Vector2D pos) { pos_ = pos; };
private:
	Point2D pos_;
	Vector2D dir_;	// A efectos practico es la velocida de pacman (Up, Down, Left y Right)
	Texture* texture_;
	Game* game_;
	
	int vidasmax,vidas=0;

	bool nyom = false;
	int cool_nyom = 0;
};

