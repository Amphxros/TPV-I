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
	double width_, height_;
	Texture* texture_;
	Game* game_;
};

