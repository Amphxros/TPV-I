#pragma once
#include "checkML.h"

#include "GameCharacter.h"
#include "EventHandler.h"

class PlayState;
class Pacman	:	public GameCharacter, public EventHandler
{
public:

	Pacman() : GameCharacter(),EventHandler() { throw PacmanError("player null"); }
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

	enum State { still, moving, up, down, left, right };
	int vidas; //num de vidas actuales
	bool nyom = false; //es true si se puede comer a los fantasmas
	int cool_nyom = 0; //tiempo restante(cooldown) para comer los fantasmas
};