#pragma once
#include "Vector2D.h"
#include "Texture.h"

#include "checkML.h"
class Game;
class Pacman
{
public:
	Pacman(Point2D pos, Texture* texture, Game* game_);
	~Pacman();

	void render();
	void update();
	void handleEvents(SDL_Event& event);
	void setNyom(bool comer) { nyom = comer; };
	bool getNyom() { return nyom; };
	Vector2D getPos() { return pos_ + dir_; };

private:
	Point2D pos_;
	Vector2D dir_;	//vector auxiliar que tomar� el valor de las velocidades en funcion de si va a la izq,der,arr o abajo
	Texture* texture_;
	Game* game_;
	bool nyom = false;
};

