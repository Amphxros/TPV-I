#pragma once
#include "Vector2D.h"
#include "Texture.h"

class Game;
class Pacman
{
public:
	Pacman(Point2D pos, Vector2D speed,double width,double height, Texture* texture, Game* game_);
	~Pacman();

	void render() const;
	void update();
	void handleEvents(SDL_Event& event);

private:
	Point2D pos_;
	Vector2D speed_;
	Vector2D dir_;	//vector auxiliar que tomará el valor de las velocidades en funcion de si va a la izq,der,arr o abajo
	double width_, height_;
	Texture* texture_;
	Game* game_;
};

