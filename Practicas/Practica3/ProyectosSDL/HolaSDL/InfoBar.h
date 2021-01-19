#pragma once

#include <Vector>
#include "checkML.h"
#include "GameObject.h"
#include "consts.h"

class PlayState;
class InfoBar:
	public GameObject
{
public:
	InfoBar() : GameObject() { throw PacmanError("Info bar null"); }
	InfoBar(Vector2D pos, double width, double height, Texture* texture, Texture* nums, GameState* game);
	virtual ~InfoBar() { punt_.clear(); num_texture = nullptr; delete num_texture; }
	
	void setPuntos(int p); //cambia los puntos
	int getPuntos() { return points_; }
	
	void render();
	void update(){}
private:
	Texture* num_texture;
	int points_=0;
	std::vector<int> punt_;

	PlayState* game_state;
};

