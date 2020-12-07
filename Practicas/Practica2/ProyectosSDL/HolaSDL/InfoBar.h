#pragma once

#include <Vector>

#include "GameObject.h"
class InfoBar: public GameObject
{
public:
	InfoBar(Vector2D pos, double width, double height, Texture* texture, Texture* nums, Game* game);
	virtual ~InfoBar() { punt_.clear(); }
	void setPuntos(int p);
	int getPuntos() { return points_; }
	void render();
	void update(){}
private:
	Texture* num_texture;
	int points_=0;
	std::vector<int> punt_;
};

