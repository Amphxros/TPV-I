#pragma once
#include "Vector2D.h"
#include "Texture.h"

const int GHOST_ROW = 6;
const int GHOST_COL = 6;
class Game;
class Ghost
{
public:
	Ghost(Point2D pos, Vector2D speed,double width,double height, Texture* Texture, Game* game_,int color);
	~Ghost();

	void render() const;
	void update();

private:
	Point2D pos_;
	Vector2D speed_;
	double width_, height_;
	Texture* texture_;
	Game* game_;
	int color_;
};

