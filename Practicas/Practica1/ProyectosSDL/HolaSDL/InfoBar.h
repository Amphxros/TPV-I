#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include <Vector>

class Game;
class InfoBar
{
public:
	InfoBar(Vector2D pos, Texture* texture, Texture* nums, Game* game);
	void setPuntos(int p);
	void render();

private:
	Vector2D pos_;
	Game* game_;
	Texture* texture_; 
	Texture* num_texture;

	std::vector<int> punt_;
};

