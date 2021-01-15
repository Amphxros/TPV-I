#pragma once

#include <Vector>
#include "checkML.h"
#include "GameObject.h"
#include "consts.h"

class Game;
class InfoBar:
	public GameObject
{
public:
	InfoBar(Vector2D pos, double width, double height, Texture* texture, Texture* nums, GameState* game);
	virtual ~InfoBar() { punt_.clear(); num_texture = nullptr; }
	
	void setPuntos(int p); //cambia los puntos
	int getPuntos() { return points_; }
	
	void render();
	void update(){}
private:
	Texture* num_texture;
	int points_=0;
	std::vector<int> punt_;

	Game* game_state;
};

