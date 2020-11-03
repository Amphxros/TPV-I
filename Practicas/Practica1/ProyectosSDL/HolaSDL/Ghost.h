#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;
class Ghost
{
public:
	Ghost(Point2D pos, Vector2D speed, Texture* Texture, Game* game_);
	~Ghost();

	void render() const;
	void update();

private:
	Point2D pos_;
	Vector2D speed_;
	Texture* texture_;
	Game* game_;
};

