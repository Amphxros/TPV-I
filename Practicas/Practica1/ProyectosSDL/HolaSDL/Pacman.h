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
	void setPos(Vector2D pos) { pos_ = pos; };
private:
	Point2D pos_;
	Vector2D dir_;	// A efectos practico es la velocida de pacman (Up, Down, Left y Right)
	Texture* texture_;
	Game* game_;
	bool nyom = false;
};

