#pragma once
#include "GameCharacter.h"
#include "checkML.h"
class Game;
class Pacman: 
	public GameCharacter
{
public:
	
	Pacman(Point2D pos, double speed,double width, double height, Texture* texture, Game* game_, int numVidas);
	virtual ~Pacman();

	void render();
	void update();
	void handleEvents(SDL_Event& event);

	void setNyom(bool comer);	// Come la vitamina y activa la debilidad en los fantasmas
	bool getNyom() { return nyom; };
	
	void setVidas(int v) { vidas = v; }
	int getVidas() { return vidas; };

	Vector2D getPos() { return pos_ + dir_; };	// Devuelve la posicion a la que intenta moverse
	Vector2D getCurrPos() { return pos_; };	// Devuelve la posicion a la que intenta moverse
	
private:
	int vidasmax,vidas=0;

	bool nyom = false;
	int cool_nyom = 0;
};

