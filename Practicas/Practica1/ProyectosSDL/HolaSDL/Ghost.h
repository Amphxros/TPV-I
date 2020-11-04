#pragma once
#include "Vector2D.h"
#include "Texture.h"

const int GHOST_ROW = 6;
const int GHOST_COL = 6;
class Game;
class Ghost
{
public:
	Ghost(Point2D pos, Texture* Texture, Game* game_,int color);
	~Ghost();

	void render();
	void update();

private:
	Point2D pos_;
	Vector2D dir_;
	Texture* texture_;
	Game* game_;
	int color_;
};

