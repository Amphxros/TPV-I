#pragma once

#include <Vector>
#include "checkML.h"
#include "GameObject.h"
class InfoBar:
	public GameObject
{
public:
	InfoBar(Vector2D pos, double width, double height, Texture* texture, Texture* nums, Game* game);
	virtual ~InfoBar() { punt_.clear(); num_texture = nullptr; delete num_texture; }
	
	void setPuntos(int p); //cambia los puntos
	int getPuntos() { return points_; }
	
	void render();
	void update(){}
private:
	Texture* num_texture;
	int points_=0;
	std::vector<int> punt_;
};

