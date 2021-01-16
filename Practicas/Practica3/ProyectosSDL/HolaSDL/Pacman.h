#pragma once
#include "GameCharacter.h"
#include "EventHandler.h"

#include "checkML.h"
class Game;
class Pacman: 
	public GameCharacter, public EventHandler
{
public:
	Pacman() : GameCharacter(),EventHandler() { throw "Pacman nulo"; }
	Pacman(Point2D pos, double speed,double width, double height, Texture* texture, GameState* game_, int numVidas);
	virtual ~Pacman();

	void render();
	void update();
	bool handleEvents(SDL_Event& event);

	bool getNyom() { return nyom; };
	
	void setVidas(int v) { vidas = v; }
	int getVidas() { return vidas; };

	Vector2D getPos() { return pos_ + dir_; };	// Devuelve la posicion a la que intenta moverse
	Vector2D getCurrPos() { return pos_; };	// Devuelve la posicion a la que intenta moverse
	
private:
	int vidas; //num de vidas actuales

	bool nyom = false; //es true si se puede comer a los fantasmas
	int cool_nyom = 0; //tiempo restante para comer los fantasmas
};

