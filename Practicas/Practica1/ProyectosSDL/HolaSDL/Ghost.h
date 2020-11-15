#pragma once
#include "Vector2D.h"
#include "Texture.h"

#include "checkML.h"

const int GHOST_ROW = 6;
const int GHOST_COL = 6;
class Game;
enum directions{LEFT,RIGHT,UP,DOWN };
class Ghost
{
public:
	Ghost(Point2D pos, Texture* Texture, Game* game,int color);
	~Ghost();

	void render();
	void update();

	Vector2D getPos(){return pos_ + dir_;}

private:
	Point2D pos_;
	Vector2D dir_;
	//aqui creamos un array estatico con las posibles direcciones (0,1),(0,-1),(1,0)...
	Texture* texture_;
	Game* game_;
	int color_;
};

