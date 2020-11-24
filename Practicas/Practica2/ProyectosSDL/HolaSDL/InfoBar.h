#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include <Vector>

class Game;
class InfoBar
{
public:
	InfoBar(Vector2D pos, Texture* texture, Texture* nums, Game* game);
	~InfoBar() { punt_.clear(); }
	void setPuntos(int p);
	int getPuntos() { return points_; }
	void render();

private:
	Vector2D pos_;
	Game* game_;
	Texture* texture_; 
	Texture* num_texture;
	int points_=0;
	std::vector<int> punt_;
};

